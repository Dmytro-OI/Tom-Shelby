from youtube_transcript_api import YouTubeTranscriptApi

video_id = 'V2rj9RpucTc'


transcript_list = YouTubeTranscriptApi.list_transcripts(video_id)

for transcript in transcript_list:
    print(
        # transcript.video_id,
        # transcript.language,
        # transcript.language_code,
        transcript.is_generated,
        # transcript.is_translatable,
        # transcript.translation_languages,
    )
transcript_data = transcript.fetch()

filtered_text = [
        entry['text'] for entry in transcript_data 
        if entry['text'].strip() not in ["[Music]"]
    ]
    
for text in filtered_text:
    print(text)