from youtube_transcript_api import YouTubeTranscriptApi
from pytube import extract

class Transcriptor:
    def __init__(self, url):
        self.video_id = self.get_ID(url)

    def get_ID(self, url):
        video_id = extract.video_id(url)
        return video_id

    def transcript_text(self):
        transcript_list = YouTubeTranscriptApi.list_transcripts(self.video_id)

        full_text = ""
        
        for transcript in transcript_list:
            if transcript.is_generated:
                transcript_data = transcript.fetch()
                
                for entry in transcript_data:
                    full_text += entry['text'] + " "
                
        return full_text
    
if __name__ == "__main__":
    url = "https://www.youtube.com/watch?v=7iwgyzX-76g"  
    transcriptor = Transcriptor(url)
    transcript_text = transcriptor.transcript_text()
    print(transcript_text)