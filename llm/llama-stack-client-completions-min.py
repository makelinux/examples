#!/usr/bin/python3

# Prerequisites:
# export LLAMA_STACK_CLIENT_BASE_URL=http://localhost:8321
# export INFERENCE_MODEL=ollama/llama3.2:3b
# ollama run $INFERENCE_MODEL
# llama stack run starter

import os
from llama_stack_client import LlamaStackClient

c = LlamaStackClient()

r = c.chat.completions.create(
    model=os.getenv("INFERENCE_MODEL", "ollama/llama3.2:3b"),
    messages=[
        {"role": "system", "content": "You are a helpful assistant."},
        {"role": "user", "content": "Write a haiku about coding"},
    ],
)
print(r.choices[0].message.content)
