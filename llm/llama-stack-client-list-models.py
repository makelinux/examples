#!/usr/bin/python3

# Prerequisite:
# export LLAMA_STACK_CLIENT_BASE_URL=http://localhost:8321

from llama_stack_client import LlamaStackClient

for m in LlamaStackClient().models.list():
    print(m.custom_metadata.get("provider_id"), m.custom_metadata['model_type'], m.id)
