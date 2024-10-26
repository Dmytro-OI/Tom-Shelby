# Use a pipeline as a high-level helper
from transformers import pipeline

summarizer = pipeline("summarization", model="google/pegasus-xsum")
transcript = ""
summary = summarizer(transcript, max_length=130, min_length=30, do_sample=False)
print(summary[0]['summary_text'])