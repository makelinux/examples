#!/usr/bin/python3

from llama_stack_client import LlamaStackClient

# uses LLAMA_STACK_CLIENT_BASE_URL
for m in LlamaStackClient().models.list():
    try:
        print(m.custom_metadata.get("provider_id"), m.custom_metadata['model_type'], m.id)
    except Exception:
        try:
            print(m.model_type, m.identifier)
        except Exception:
            print(m)
