from transcription import Transcriptor
from summariser import Summariser



def main():
    t = Transcriptor("https://www.youtube.com/watch?v=LaffA9EyUgo")
    text = t.transcript_text()
    s = Summariser()
    summary = s.get_summary(text, 100)

    with open("summary.txt", mode="w") as f:
        f.write(summary)



if __name__ == "__main__":
    main()