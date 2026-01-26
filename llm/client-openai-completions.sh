curl -s ${LLAMA_STACK_CLIENT_BASE_URL:-http://localhost:8321}/v1/chat/completions \
  -H "Content-Type: application/json" \
  -d '{
    "model": "'${INFERENCE_MODEL:-ollama/llama3.2:3b}'",
    "messages": [ { "role": "user", "content": "Hi" } ]
  }' | jq .

