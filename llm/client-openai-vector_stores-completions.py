#!/usr/bin/python3

"""
Demo script showing RAG with Chat Completions API - Manual retrieval with explicit control

Run this script after starting a Llama Stack server:
    llama stack run starter
"""

import io
import os

import requests
from openai import OpenAI

c = OpenAI(base_url="http://localhost:8321/v1/", api_key="none")

vs = c.vector_stores.create()
buf = io.BytesIO(str("abc is green").encode('utf-8'))

fid = c.files.create(file=("aa.txt", buf), purpose="assistants").id
c.vector_stores.files.create(vs.id, file_id=fid)

query = "color of abc"

res = c.vector_stores.search(vs.id, query=query, max_num_results=3, rewrite_query=False)

context = "\n\n".join([ci.text for r in res.data for ci in r.content])

completion = c.chat.completions.create(
    model=os.getenv("INFERENCE_MODEL", "ollama/llama3.2:3b"),
    messages=[
        {
            "role": "system",
            "content": "You are a helpful assistant",
        },
        {
            "role": "user",
            "content": f"Context:\n{context}\n\nQuestion: {query}",
        },
    ],
    temperature=0.7,
)

print(completion.choices[0].message.content)
