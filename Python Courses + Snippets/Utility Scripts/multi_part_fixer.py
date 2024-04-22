# recursively search for files in a directory that match a regex pattern

import argparse
import os
import re
from mutagen.mp3 import EasyMP3
from mutagen.oggopus import OggOpus

parser = argparse.ArgumentParser(description='Manually fix files in a directory (and all sub-dirs) that have multiple parts in artist or title.')
parser.add_argument('directory', type=str, help='The directory to search in.')

MULTI_PART_PATTERN = re.compile(r'\s+[\-_]\s+', re.IGNORECASE)

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
  
def parts_from(s):
    return set(re.split(MULTI_PART_PATTERN, s))
 
def tag(audio, file_name):
  search_in = [
    file_name,
    audio['title'][0] if 'title' in audio else '',
    audio['artist'][0] if 'artist' in audio else ''
  ]
  parts = list(set().union(*map(parts_from, search_in)))

  def get_part(part_name):
      nonlocal parts

      print(f"which of the parts is the {part_name}?, enter 0 to skip")
      for i, part in enumerate(parts):
          print("{}: {}".format(i + 1, part))

      while True:
          try:
              part_index = int(input())
              if part_index == 0:
                  return None
              if part_index < 1 or part_index > len(parts):
                  raise ValueError
              break
          except ValueError:
              print("Invalid input!")

      part = parts[part_index - 1]
      parts = parts[:part_index - 1] + parts[part_index:] # remove the part from the list
      return part

  artist = get_part('artist')
  if artist is None:
      return False
  title = parts.pop() if len(parts) == 1 else get_part('title')

  if artist and title:
      audio['artist'] = artist
      audio['title'] = title
      audio.save()
      
      print('==============================')
      print('Tagged: ' + file_name)
      print('------------------------------')
      print('\tArtist:\t' + artist)
      print('\tTitle:\t' + title)
      print('==============================')
      return True

  return False


def main():
    args = parser.parse_args()
    directory = args.directory
    
    curr = fixed = skipped = 0
    total = sum(len(fs) for _, _, fs in os.walk(directory))
    
    for root, dirs, files in os.walk(directory):
        for file in files:
            curr += 1
            file_path = os.path.join(root, file)
            
            try: 
                audio = EXTS.get(get_file_extension(file))
                if audio is None:
                    continue
                audio = audio(file_path)
                title = audio['title'][0] if 'title' in audio else ''
                artist = audio['artist'][0] if 'artist' in audio else ''
                if re.search(MULTI_PART_PATTERN, title.lower()) or re.search(MULTI_PART_PATTERN, artist.lower()):
                    print(f"({curr}/{total}) File {file} has multiple parts in artist or title.")
                    print(f"Artist: {artist}")
                    print(f"Title: {title}")
                    print()
                    if tag(audio, get_file_name(file)):
                        fixed += 1
                    else:
                        print('Skipped: ' + file_path)
                        skipped += 1
                    print()
                
            except Exception as e:
                print(f"Error processing file {file_path}: {e}")
            
    print(f"\n\n>>> Done! Fixed {fixed} out of {total} files. Skipped {skipped} files.")
if __name__ == "__main__":
    try:
      main()
    except KeyboardInterrupt:
      print('\n\n>>> Exited by user. (SOME FILES MAY NOT HAVE BEEN FIXED!)')