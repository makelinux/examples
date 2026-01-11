#!/usr/bin/python3

import os
from typing import TypedDict
from langchain_openai import ChatOpenAI
from langgraph.graph import StateGraph, END

class State(TypedDict):
    input: str
    llm_output: str
    token_count: int

def llm_node(state):
    """Initializes an LLM and returns its output content."""
    model = ChatOpenAI(base_url=os.getenv("OPENAI_EP", "http://localhost:8321/v1/"), #api_key="none",
                       model=os.getenv("INFERENCE_MODEL", "gemini/models/gemini-flash-latest"))
    output = model.invoke(state["input"])
    return {"llm_output": output.content}

def token_counter_node(state):
    """Counts the number of tokens (words) in a string."""
    tokens = str(state["llm_output"]).split()
    count_no = len(tokens)
    print(f"Token count: {count_no}")
    return {"token_count": count_no}

workflow = StateGraph(State)

workflow.add_node('LLM_Model', llm_node)
workflow.add_node('Get_Token_Counter', token_counter_node)

workflow.add_edge('LLM_Model', 'Get_Token_Counter')
workflow.add_edge('Get_Token_Counter', END)

workflow.set_entry_point('LLM_Model')

app = workflow.compile()

final_result = app.invoke({"input": "Explain the concept of AI agents in one sentence."})
print(f"Final result:\n{final_result['llm_output']}")

