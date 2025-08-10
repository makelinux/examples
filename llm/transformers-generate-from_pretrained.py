#!/usr/bin/env python3

print("Loading...")
import torch
from transformers import AutoTokenizer, AutoModelForSequenceClassification, AutoModelForCausalLM

# Load model and tokenizer from directory (e.g., for text classification)
model_dir = 'results/checkpoint-4'
#tokenizer = AutoTokenizer.from_pretrained(model_dir)
tokenizer = AutoTokenizer.from_pretrained("gpt2")
# model = AutoModelForSequenceClassification.from_pretrained(model_dir)
model = AutoModelForCausalLM.from_pretrained(model_dir)

text = "0 1"

inputs = tokenizer(text, return_tensors="pt")
print(inputs)

# Perform inference
with torch.no_grad():
    outputs = model(**inputs)

# Get predicted class
#predictions = torch.argmax(outputs.logits, dim=-1)
#print(f"Predicted class: {predictions.item()}")

# For text generation (if using a language model like GPT)
generated = model.generate(inputs['input_ids'], max_length=4)
generated_text = tokenizer.decode(generated[0], skip_special_tokens=True)
print(generated_text)

