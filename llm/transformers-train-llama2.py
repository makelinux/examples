#!/usr/bin/env python3

print("Initializing...")

import os
from datasets import DatasetDict, disable_progress_bar
from datasets.arrow_dataset import Dataset
from transformers.utils import logging
from transformers import AutoTokenizer, DataCollatorForLanguageModeling, Trainer, TrainingArguments
from transformers import pipeline, LlamaConfig, LlamaForCausalLM
from difflib import SequenceMatcher

# ========== Setup ========== #
os.environ["WANDB_DISABLED"] = "true"
os.environ["DS_ACCELERATOR"] = "cpu"
logging.set_verbosity(logging.ERROR)
disable_progress_bar()

# ========== Generate Toy Data ========== #
length = 8
input_text = " ".join(str(i) for i in range(length))
print("input:", input_text)

ds = DatasetDict({
    "train": Dataset.from_list([{"text": input_text + ' 0 0'}]),
    "valid": Dataset.from_list([{"text": input_text + ' 0 0'}])
})

#samples = [{"text": " ".join(str(i + j) for i in range(8))} for j in range(100)]
#ds = DatasetDict({
#    "train": Dataset.from_list(samples),
#    "valid": Dataset.from_list(samples[:20])
#})

#print(samples)

# ========== Model Configuration ========== #
config = LlamaConfig(
    vocab_size=32000,
    hidden_size=512,
    intermediate_size=512,
    num_hidden_layers=4,
    num_attention_heads=4,
    max_position_embeddings=128,
    rms_norm_eps=1e-6,
    initializer_range=0.02,
    pad_token_id=0,
    bos_token_id=1,
    eos_token_id=2
)

model = LlamaForCausalLM(config)

# ========== Tokenizer ========== #
tokenizer = AutoTokenizer.from_pretrained("TinyLlama/TinyLlama-1.1B-Chat-v1.0")

# Set pad_token if missing
if tokenizer.pad_token is None:
    tokenizer.add_special_tokens({'pad_token': '[PAD]'})
    print("Added pad_token.")

# Resize model to match tokenizer
model.resize_token_embeddings(len(tokenizer))

# Save tokenizer (optional)
tokenizer.save_pretrained("tokenizer.llama")

# ========== Tokenization ========== #
def tokenize_function0(examples):
    return tokenizer(examples["text"], padding="max_length", truncation=True, max_length=length)

def tokenize_function(examples):
    return tokenizer(examples["text"], padding="max_length", truncation=True, max_length=length, return_tensors=None, add_special_tokens=True)


tokenized_datasets = ds.map(tokenize_function, batched=True, remove_columns=["text"])

# ========== Data Collator ========== #
dc = DataCollatorForLanguageModeling(tokenizer=tokenizer, mlm=False)

# ========== Training Arguments ========== #
training_args = TrainingArguments(
    output_dir='./results',
    per_device_train_batch_size=1,
    gradient_accumulation_steps=16,
    num_train_epochs=20,
    learning_rate=2e-4,
    logging_steps=1,
    save_steps=100,
    save_total_limit=2,
    warmup_steps=5,
    weight_decay=0.01,
    dataloader_num_workers=0,
    fp16=False,
    optim="adamw_torch",
    logging_dir='./logs',
    report_to="none"
)

# ========== Training ========== #
trainer = Trainer(
    model=model,
    args=training_args,
    train_dataset=tokenized_datasets["train"],
    eval_dataset=tokenized_datasets["valid"],
    data_collator=dc,
)

print("Training...")
train_output = trainer.train()
print("Training output:", train_output)

generator = pipeline("text-generation", model=model, tokenizer=tokenizer)

output = generator(input_text, max_length=length + 10, num_return_sequences=1)[0]['generated_text']
print("Similarity:", SequenceMatcher(None, input_text, output).ratio())
print(f"Generated output: '{output}'")

model.save_pretrained('trained_model.llama')
tokenizer.save_pretrained('trained_model.llama')
