import os
import time
import re

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

# Set to true to fix titles with irrelevant stuff in them (e.g. " - YouTube" / " - Official Video" / " feat. <artist>" / " (HD)" etc.)
FIX_TITLES = True

IRRELEVANT_TITLE_SUFFIXES = [
    "\s+\(feat.+",
    "\s+\[feat.+",
    "\s+【feat.+",
    "\s+.?\s+Official\s+(Video|Audio).+",
    "\s+.?\s+HD.+",
    "\s+.?\s+HQ.+",
    "\s+.?\s+Lyrics.+",
    "\s+\-?\s?$", # remove trailing spaces and dashes
]



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
    file_extension = get_file_extension(file_path)
    
    tagged = fixed = False
    
    audio = mutagen.File(file_path)
    if audio is None:
        print('!!! ERROR: Could not open file: ' + file_path)
        return False
    
    if ' - ' in file_name:
        artist = file_name[:file_name.find(' - ')]
        title = file_name[file_name.find(' - ') + 3:]
        if not artist or not title:
            return False
    else:
        if file_extension == 'mp3':
            artist = audio['TPE1'].text[0] if 'TPE1' in audio.tags else ''
            title = audio['TIT2'].text[0] if 'TIT2' in audio.tags else ''
            if not artist or not title:
                return False
        elif file_extension == 'opus':
            artist = audio['artist'][0] if 'artist' in audio else ''
            title = audio['title'][0] if 'title' in audio else ''
            if not artist or not title:
                return False
    
    
    if file_extension == 'mp3':
        if audio.tags is None:
            audio.add_tags()
        if 'TPE1' not in audio.tags:
            audio['TPE1'] = TPE1(text=artist)
            tagged = True
        if 'TIT2' not in audio.tags:
            audio['TIT2'] = TIT2(text=title)
            tagged = True
        elif FIX_TITLES:
            for suffix in IRRELEVANT_TITLE_SUFFIXES:
                if re.search(suffix, audio['TIT2'].text[0], re.IGNORECASE):
                    print(f'Fixed title: {audio["TIT2"].text[0]} -> {re.sub(suffix, "", audio["TIT2"].text[0], 0, re.IGNORECASE)}')
                    audio['TIT2'].text[0] = re.sub(suffix, '', audio['TIT2'].text[0], 0, re.IGNORECASE)
                    fixed = True
    elif file_extension == 'opus':
        if 'artist' not in audio:
            audio['artist'] = artist
            tagged = True
        if 'title' not in audio:
            audio['title'] = title
            tagged = True
        elif FIX_TITLES:
            for suffix in IRRELEVANT_TITLE_SUFFIXES:
                if re.search(suffix, audio['title'][0], re.IGNORECASE):
                    print(f'Fixed title: {audio["title"][0]} -> {re.sub(suffix, "", audio["title"][0], 0, re.IGNORECASE)}')
                    audio['title'] = re.sub(suffix, '', audio['title'][0], 0, re.IGNORECASE)
                    fixed = True

    if tagged:
        # audio.save()
        print('Tagged: ' + file_path)
    elif fixed:
        # audio.save()
        pass
    return { 'tagged': tagged, 'fixed': fixed }


# recursively tag all mp3/opus files in a directory
def tag_directory(directory):
    folder_stack = [directory]  # dfs stack
    amount_tagged, amount_fixed, last = 0, 0, 0
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
                    results = tag_if_missing(file_path)
                    last += 1
                    if results:
                        amount_tagged += int(results['tagged'])
                        amount_fixed += int(results['fixed'])
    return { 'tagged': amount_tagged, 'fixed': amount_fixed }


if __name__ == '__main__':
    inp = None
    while inp not in {'y', 'n', 'Y', 'N'}:
        inp = input('Are you sure you want to tag all mp3/opus files in this directory and all sub-directories? (y/n)')
    if inp in {'y', 'Y'}:
        start_time = time.time()
        totals = tag_directory(os.getcwd())
        total_tagged = totals['tagged']
        total_fixed = totals['fixed']

        seconds_took = time.time() - start_time
        if seconds_took < 60:
            time_took = f"{round(seconds_took, 2)} seconds"
        else:
            time_took = f"{seconds_took // 60} minutes, and {round(seconds_took % 60, 2)} seconds"

        print('\n\n>>> Done!')
        print('>>> Tagged ' + str(total_tagged) + ' and fixed ' + str(total_fixed) + ' files in ' + time_took)
        input('\nPress enter to exit.')
    else:
        print('Cancelled.')
