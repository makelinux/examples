#!/usr/bin/python3

import os
from llama_stack_client import Agent, AgentEventLogger, LlamaStackClient
import requests
from io import BytesIO

c = LlamaStackClient(base_url="http://localhost:8321")

vs = c.vector_stores.create(name="my_vector_db")

buf = BytesIO(str("abc is green").encode('utf-8'))
buf.name = "abc"

file = c.files.create(file=("a.txt", buf), purpose="assistants")
c.vector_stores.files.create(vector_store_id=vs.id, file_id=file.id)

agent = Agent(
    c,
    model=os.getenv("INFERENCE_MODEL", "vertexai/google/gemini-2.5-flash"),
    instructions="You are a helpful assistant",
    tools=[
        { "type": "file_search", "vector_store_ids": [vs.id], }
    ],
)

res = agent.create_turn(
    messages=[{"role": "user", "content":
               "What is the color of abc?"
               }],
    session_id=agent.create_session("my_session"),
    stream=True,
)

for log in AgentEventLogger().log(res):
    print(log, end="")
