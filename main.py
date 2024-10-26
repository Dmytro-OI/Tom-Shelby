from transcription import Transcriptor
from summarizer import Summarizer



def main():
    t = Transcriptor("https://www.youtube.com/watch?v=OiUS2926nQM")
    text = t.transcript_text()
    s = Summarizer()
    summary = s.get_summary(text, 100)
    print(summary)



if __name__ == "__main__":
    main()