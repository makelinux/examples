#!/usr/bin/python3

# export INFERENCE_MODEL=llama3.2:1b-instruct-fp16
## start ollama:
# ollama run $INFERENCE_MODEL
## start llama-stack:
# uv run --with llama-stack llama stack build --template ollama --image-type venv --image-name ~/my-ollama-llama-stack --run

import os
from llama_stack_client import LlamaStackClient

c = LlamaStackClient(base_url="http://localhost:8321")

r = c.chat.completions.create(
    model=os.getenv("INFERENCE_MODEL", "gemini/models/gemini-2.5-pro"),
    messages=[
        {"role": "system", "content": "You are a helpful assistant."},
        {"role": "user", "content": "Write a haiku about coding"},
    ],
)
print(r.choices[0].message.content)
