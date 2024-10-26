from transcription import Transcriptor



def main():
    t = Transcriptor("Lwnd0EonRiM")
    text = t.transcript_text()
    print(text)



if __name__ == "__main__":
    main()