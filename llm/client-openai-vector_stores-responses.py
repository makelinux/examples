#!/usr/bin/python3

# Prerequisite:
# export OPENAI_BASE_URL=$LLAMA_STACK_CLIENT_BASE_URL/v1

# ./llama-stack/docs/docs/getting_started/demo_script.py

import io, os, requests
from openai import OpenAI

c = OpenAI()

vs = c.vector_stores.create()
buf = io.BytesIO(str("abc is green").encode('utf-8'))

fid = c.files.create(file=("aa.txt", buf), purpose="assistants").id
c.vector_stores.files.create(vs.id, file_id=fid)

resp = c.responses.create(
    model=os.getenv("INFERENCE_MODEL", "ollama/llama3.2:3b"),
    input="What is the color of abc?",
    tools=[{"type": "file_search", "vector_store_ids": [vs.id]}],
#    include=["file_search_call.results"],
)

print(resp.output[-1].content[-1].text)
