from transcription import Transcriptor
from summariser import Summariser

from fastapi import FastAPI
from pydantic import BaseModel


class SummaryBody(BaseModel):
    link: str
    lang: str
    max_length: float

app = FastAPI()


@app.post("/")
async def get_summary(body: SummaryBody):
    print("here")
    t = Transcriptor(body.link)
    text = t.transcript_text()
    print("here")
    s = Summariser()
    summary = s.get_summary(text, body.max_length)

    return {"status": 200, "data": {"summary": summary}}
