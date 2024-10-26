from youtube_transcript_api import YouTubeTranscriptApi

class Transcriptor:
    def __init__(self,video_id):
        self.video_id = video_id

    def transcript_text(self):
        transcript_list = YouTubeTranscriptApi.list_transcripts(self.video_id)

        all_filtered_text = []
        for transcript in transcript_list:
            print(
                transcript.is_generated,
            )
        transcript_data = transcript.fetch()

        filtered_text = [
                entry['text'] for entry in transcript_data 
                if entry['text'].strip() not in ["[Music]"]
            ]
        all_filtered_text.extend(filtered_text)
        return all_filtered_text
