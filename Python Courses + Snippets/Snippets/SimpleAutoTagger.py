import os
import time

import mutagen
from mutagen.id3 import TPE1, TIT2

# Written by https://github.com/el-f
# This script is a simple auto-tagger for mp3 and opus files.
# It will read the file's name and if it follows the following format: <artist> - <title>.<file_extension>
# and the tags are missing it will set the tags accordingly.


# Set to True to tag all folders in the current directory
TAG_ALL_FOLDERS = True

# Set to a set of prefixes to only tag folders that start with one of these prefixes
MUSIC_FOLDER_PREFIXES = {'MP'}

# Set to a set of known folder names to only tag folders that have one of these names
MUSIC_FOLDER_KNOWN_NAMES = {'Music'}


def get_file_name(file_path):
    name = os.path.basename(file_path)
    return name[:name.rfind('.')]


def get_file_extension(file_path):
    name = os.path.basename(file_path)
    return name[name.rfind('.') + 1:]


def is_untagged_folder(folder):
    if TAG_ALL_FOLDERS:
        return True
    folder_name = os.path.basename(folder)
    for prefix in MUSIC_FOLDER_PREFIXES:
        if folder_name.startswith(prefix):
            return True
    for known_name in MUSIC_FOLDER_KNOWN_NAMES:
        if folder_name == known_name:
            return True
    return False


# automatically tag mp3 files using the following format: <artist> - <title>.<file_extension>
# with the artist and title if not already set
def tag_if_missing(file_path):
    file_name = get_file_name(file_path)
    if ' - ' not in file_name:
        return False

    artist = file_name[:file_name.find(' - ')]
    title = file_name[file_name.find(' - ') + 3:]
    if not artist or not title:
        return False

    tagged = False
    audio = mutagen.File(file_path)
    if audio is None:
        print('!!! ERROR: Could not open file: ' + file_path)
        return False

    file_extension = get_file_extension(file_path)
    if file_extension == 'mp3':
        if audio.tags is None:
            audio.add_tags()
        if 'TPE1' not in audio.tags:
            audio['TPE1'] = TPE1(text=artist)
            tagged = True
        if 'TIT2' not in audio.tags:
            audio['TIT2'] = TIT2(text=title)
            tagged = True
    elif file_extension == 'opus':
        if 'artist' not in audio:
            audio['artist'] = artist
            tagged = True
        if 'title' not in audio:
            audio['title'] = title
            tagged = True

    if tagged:
        audio.save()
        print('Tagged: ' + file_path)
    return tagged


# recursively tag all mp3/opus files in a directory
def tag_directory(directory):
    folder_stack = [directory]  # dfs stack
    amount_tagged, last = 0, 0
    while folder_stack:
        folder = folder_stack.pop()
        if is_untagged_folder(folder):
            print((last != 0) * '\n\n' + '>>> Tagging: ' + folder)
            last = 0
            for file in os.listdir(folder):
                file_path = os.path.join(folder, file)
                if os.path.isdir(file_path):
                    folder_stack.append(file_path)
                elif file_path.endswith('.mp3') or file_path.endswith('.opus'):
                    if tag_if_missing(file_path):
                        amount_tagged += 1
                        last += 1
    return amount_tagged


if __name__ == '__main__':
    inp = None
    while inp not in {'y', 'n', 'Y', 'N'}:
        inp = input('Are you sure you want to tag all mp3/opus files in this directory and all sub-directories? (y/n)')
    if inp in {'y', 'Y'}:
        start_time = time.time()
        total_tagged = tag_directory(os.getcwd())

        seconds_took = time.time() - start_time
        if seconds_took < 60:
            time_took = f"{round(seconds_took, 2)} seconds"
        else:
            time_took = f"{seconds_took // 60} minutes, and {round(seconds_took % 60, 2)} seconds"

        print('\n\n>>> Done!')
        print('>>> Tagged ' + str(total_tagged) + ' files in ' + time_took)
        input('\nPress enter to exit.')
    else:
        print('Cancelled.')
