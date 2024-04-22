import argparse
import os
import re
from mutagen.mp3 import EasyMP3
from mutagen.oggopus import OggOpus

parser = argparse.ArgumentParser(description='Recursively search for files in a directory that match a regex pattern.')
parser.add_argument('directory', type=str, help='The directory to search in.')
parser.add_argument('pattern', type=str, help='The regex pattern to search for.')

EXTS = {
    'mp3': EasyMP3,
    'opus': OggOpus,
}

def get_file_name(file_path):
    name = os.path.basename(file_path)
    return name[:name.rfind('.')]


def get_file_extension(file_path):
    name = os.path.basename(file_path)
    return name[name.rfind('.') + 1:]


def main():
    args = parser.parse_args()
    directory = args.directory
    pattern = args.pattern.lower()

    for root, dirs, files in os.walk(directory):
        for file in files:
            try: 
                audio = EXTS.get(get_file_extension(file))
                if audio is None:
                    continue
                audio = audio(os.path.join(root, file))
                title = str(audio['title'] if 'title' in audio else '')
                artist = str(audio['artist'] if 'artist' in audio else '')
                if re.search(pattern, title.lower()):
                    print(f"Found pattern in title: {title} for file {os.path.join(root, file)}")
                if re.search(pattern, artist.lower()):
                    print(f"Found pattern in artist: {artist} for file {os.path.join(root, file)}")
            except Exception as e:
                print(f"Error processing file {os.path.join(root, file)}: {e}")
            
                
if __name__ == "__main__":
    main()