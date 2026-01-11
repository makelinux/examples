#!/usr/bin/python3

import os
from langchain_openai import ChatOpenAI
from langchain_core.runnables import RunnableLambda
from langchain_core.output_parsers import StrOutputParser

def token_counter(text):
    tokens = str(text).split()
    count = len(tokens)
    print(f"Token count: {count}")
    return {"output": text, "token_count": count}

model = ChatOpenAI(
    base_url=os.getenv("OPENAI_EP", "http://localhost:8321/v1/"),
    api_key="none",
    model=os.getenv("INFERENCE_MODEL", "gemini/models/gemini-flash-latest")
)

chain = model | StrOutputParser() | RunnableLambda(token_counter)

result = chain.invoke("Explain the concept of AI agents in one sentence.")
print(f"Final result:\n{result['output']}")
