#!/usr/bin/python3

# Prerequisite:
# export OPENAI_BASE_URL=$LLAMA_STACK_CLIENT_BASE_URL/v1

import os

from openai import OpenAI

c = OpenAI()

completion = c.chat.completions.create(
    model=os.getenv("INFERENCE_MODEL", "ollama/llama3.2:3b"),
    messages=[ { "role": "user", "content": "Hi", }, ],
)

print(completion.choices[0].message.content)
