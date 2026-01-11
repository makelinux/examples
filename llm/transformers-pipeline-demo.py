#!/usr/bin/env python3

print("initializing")

from transformers import pipeline, GPT2LMHeadModel, AutoTokenizer

length = 4
input = " ".join(str(i) for i in range(length))
print("input:", input)
input_list = input.split()

model = GPT2LMHeadModel.from_pretrained('trained_model')
tokenizer = AutoTokenizer.from_pretrained("gpt2")
tokenizer.pad_token = tokenizer.eos_token

print("inference")
gen = pipeline("text-generation", model=model, tokenizer=tokenizer, truncation=True)
output = gen(input_list[0], max_new_tokens=length - 1, num_return_sequences=1)[0]['generated_text']
print(output)
print(gen('0 1', max_new_tokens=length - 2, num_return_sequences=1)[0]['generated_text'])
exit(output != input)
