#!/usr/bin/env python3

print("Loading...")

import dspy

print("Connecting...")

#lm = dspy.LM('gemini/gemini-2.5-pro-preview-03-25', api_key='GEMINI_API_KEY')

#dspy.settings.configure(track_usage=True)

import os
lm = dspy.LM(
    model="openai/" + os.getenv("INFERENCE_MODEL", "gemini/models/gemini-flash-latest"),
    api_base=os.getenv("OPENAI_EP", "http://localhost:8321/v1"),
    api_key="none"
)

print(len(lm.history))
dspy.configure(lm=lm, track_usage=True)

result1 = lm("Say this is a test!", temperature=0.7)
print("Result 1:", result1)

result2 = lm(messages=[{"role": "user", "content": "Say this is a test!"}])
print("Result 2:", result2)

# Define a module (ChainOfThought) and assign it a signature (return an answer, given a question).
qa = dspy.ChainOfThought('question -> answer')

# Run with the default LM configured with `dspy.configure` above.
r = qa(question="How many floors are in the castle David Gregory inherited?")
print(r.reasoning)
print(r.answer)

c = dspy.Predict('sentence -> sentiment: bool')
print(c(sentence="it's a charming and often affecting journey.").sentiment)


if False:
    class Hop(dspy.Module):
        def __init__(self, num_docs=10, num_hops=4):
            self.num_docs, self.num_hops = num_docs, num_hops
            self.generate_query = dspy.ChainOfThought('claim, notes -> query')
            self.append_notes = dspy.ChainOfThought('claim, notes, context -> new_notes: list[str], titles: list[str]')

        def forward(self, claim: str) -> list[str]:
            notes = []
            titles = []

            for _ in range(self.num_hops):
                query = self.generate_query(claim=claim, notes=notes).query
                context = search(query, k=self.num_docs)
                prediction = self.append_notes(claim=claim, notes=notes, context=context)
                notes.extend(prediction.new_notes)
                titles.extend(prediction.titles)

            return dspy.Prediction(notes=notes, titles=list(set(titles)))
    hop = Hop()
    print(hop(claim="Stephen Curry is the best 3 pointer shooter ever in the human history"))

print(len(lm.history))
