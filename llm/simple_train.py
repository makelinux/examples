#!/usr/bin/env python3

print("initializing")

import os
os.environ["WANDB_DISABLED"] = "true"
os.environ["DS_ACCELERATOR"] = "cpu"
os.environ["HF_DATASETS_DISABLE_CACHING"] = "1"

from datasets import DatasetDict, disable_progress_bar
from datasets.arrow_dataset import Dataset
from transformers.utils import logging

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

ds.save_to_disk("test_dataset")
from transformers import AutoTokenizer

tokenizer = AutoTokenizer.from_pretrained("gpt2")

tokenizer.pad_token = tokenizer.eos_token

# Tokenize the ds
def tokenize_function(examples):
    return tokenizer(examples["text"], max_length=length)

tokenized_datasets = ds.map(tokenize_function, batched=True, remove_columns=["text"])

from transformers import GPT2Config, GPT2LMHeadModel

# https://huggingface.co/docs/transformers/model_doc/gpt2#transformers.GPT2Config
config = GPT2Config( vocab_size=tokenizer.vocab_size, n_positions=128, n_ctx=128,
    n_embd=256, n_layer=2 * length, n_head=length)

print("loading model")

model = GPT2LMHeadModel(config)

from transformers import DataCollatorForLanguageModeling, Trainer, TrainingArguments

dc = DataCollatorForLanguageModeling(tokenizer=tokenizer, mlm=False)

# https://huggingface.co/docs/transformers/main_classes/trainer#transformers.TrainingArguments
training_args = TrainingArguments(
    run_name="test",
    num_train_epochs=20,
    use_cpu=True,
    output_dir="./results",
    overwrite_output_dir=True,
    eval_strategy="steps",
)

from transformers import pipeline

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
#eval_results = trainer.evaluate()
#print(f"Perplexity: {eval_results['eval_loss']}")

print("inference")
gen = pipeline("text-generation", model=model, tokenizer=tokenizer)
output = gen(input_list[0], max_new_tokens=length - 1, num_return_sequences=1)[0]['generated_text']
print("output:", output)
if input == output:
    print('pass')
else:
    print('fail')
    exit(1)
