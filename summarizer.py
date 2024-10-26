import math
from typing import List
from transformers import pipeline



class MaxLengthExpection(Exception):
    pass

class Summarizer:
    def __init__(self, model:str="facebook/bart-large-cnn"):
        self.model = model
        self.summarizer = pipeline("summarization", model="facebook/bart-large-cnn")


    def generate_chunks(self, data:str) -> List[str]:
        chunk_size = max(math.ceil(len(data)/5), 1000)
        return [data[i:i+chunk_size] for i in range(0, len(data), chunk_size)]


    def get_summary(self, data:str, max_lenght:int) -> str:
        n_words = len(data.split())
        if n_words < max_lenght:
            raise MaxLengthExpection("max_length should be less than number of words in data")
        
        
        chunks = self.generate_chunks(data)

        summary = ""
        for chunk in chunks:
            max_length = max(int(len(chunk.split()) * 0.5), 20)
            summary += self.summarizer(chunk, max_length=max_length)[0]['summary_text'] + '\n'
        
        return summary

