#!/usr/bin/env python3

from transformers import pipeline

model = pipeline("text-generation")


def predict(prompt):
    completion = model(prompt)[0]["generated_text"]
    return completion

print(predict("My favorite programming language is"))
