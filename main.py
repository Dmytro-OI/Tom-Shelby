from transcription import Transcriptor
from summarizer import Summarizer



def main():
    t = Transcriptor("https://www.youtube.com/watch?v=LaffA9EyUgo")
    text = t.transcript_text()
    s = Summarizer()
    summary = s.get_summary(text, 100)

    with open("summary.txt", mode="w") as f:
        f.write(summary)



if __name__ == "__main__":
    main()