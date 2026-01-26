#!/usr/bin/python3

# Prerequisite:
# export OPENAI_BASE_URL=$LLAMA_STACK_CLIENT_BASE_URL/v1

import os
from openai import OpenAI

c = OpenAI()

resp = c.responses.create(
    model=os.getenv("INFERENCE_MODEL", "ollama/llama3.2:3b"),
    input="Hi",
)

print(resp.output[-1].content[-1].text)
