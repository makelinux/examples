#!/usr/bin/env python3

print("initializing")

import os
os.environ["WANDB_DISABLED"] = "true"
os.environ["DS_ACCELERATOR"] = "cpu"
os.environ["HF_DATASETS_DISABLE_CACHING"] = "1"

from datasets import DatasetDict, disable_progress_bar
from datasets.arrow_dataset import Dataset
from transformers.utils import logging
from transformers import GPT2Config, GPT2LMHeadModel
from transformers import AutoTokenizer
from transformers import DataCollatorForLanguageModeling, Trainer, TrainingArguments
from transformers import pipeline
from difflib import SequenceMatcher
import torch

logging.set_verbosity(logging.ERROR)

length = 4
input = " ".join(str(i) for i in range(length))
print("input:", input)
input_list = input.split()

disable_progress_bar()
import pyarrow as pa
train_data = pa.Table.from_pydict({"text": [input]})
valid_data = pa.Table.from_pydict({"text": [input]})
ds = DatasetDict({
    "train": Dataset(train_data, fingerprint="train"),
    "valid": Dataset(valid_data, fingerprint="valid")
})

tokenizer= AutoTokenizer.from_pretrained("gpt2")

tokenizer.pad_token = tokenizer.eos_token

# Tokenize the ds
def tokenize_function(examples):
    return tokenizer(examples["text"], max_length=length)

tokenized_datasets = ds.map(tokenize_function, batched=True, remove_columns=["text"])

print("model")
# https://huggingface.co/docs/transformers/model_doc/gpt2#transformers.GPT2Config
config = GPT2Config( vocab_size=tokenizer.vocab_size, n_positions=128, n_ctx=128,
    n_embd=256, n_layer=2 * length, n_head=length)


model = GPT2LMHeadModel(config)

dc = DataCollatorForLanguageModeling(tokenizer=tokenizer, mlm=False)

# https://huggingface.co/docs/transformers/main_classes/trainer#transformers.TrainingArguments
training_args = TrainingArguments(
    run_name="test",
    num_train_epochs=20,
    output_dir="./results",
    overwrite_output_dir=True,
    eval_strategy="steps",
    use_cpu=True,
)

trainer = Trainer(
    model=model,
    args=training_args,
    train_dataset=tokenized_datasets["train"],
    eval_dataset=tokenized_datasets["valid"],
    data_collator=dc,
)
print("training")
t = trainer.train()
print(t)

print("inference")
gen = pipeline("text-generation", model=model, tokenizer=tokenizer)
output = gen(input_list[0], max_new_tokens=length - 1, num_return_sequences=1)[0]['generated_text']
print(SequenceMatcher(None, input, output).ratio(), output)
tokenizer.save_pretrained('trained_model')

# https://github.com/ggml-org/llama.cpp/issues/11345
model.lm_head.weight = torch.nn.Parameter(model.transformer.wte.weight.clone().detach())
model.tie_word_embeddings = False

model.save_pretrained('trained_model')
