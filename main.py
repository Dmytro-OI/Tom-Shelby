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

    t = Transcriptor(body.link)
    text = t.transcript_text()
    s = Summariser()
    summary = s.get_summary(text, 100)

    return {"status": 200, "data": {"summary": summary}}
