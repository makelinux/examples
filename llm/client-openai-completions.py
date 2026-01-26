#!/usr/bin/python3

import os

from openai import OpenAI

c = OpenAI(base_url="http://localhost:8321/v1/", api_key="none")

completion = c.chat.completions.create(
    model=os.getenv("INFERENCE_MODEL", "ollama/llama3.2:3b"),
    messages=[ { "role": "user", "content": "Hi", }, ],
)

print(completion.choices[0].message.content)
