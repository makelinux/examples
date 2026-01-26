#!/usr/bin/python3

import os
from openai import OpenAI

c = OpenAI(base_url="http://localhost:8321/v1/", api_key="none")

resp = c.responses.create(
    model=os.getenv("INFERENCE_MODEL", "ollama/llama3.2:3b"),
    input="Hi",
)

print(resp.output[-1].content[-1].text)
