import os
from mutagen.mp3 import EasyMP3
from mutagen.oggopus import OggOpus
import sys

EXTS = {
    'mp3': EasyMP3,
    'opus': OggOpus,
}

HELP_MSG = """
    Usage: python TagsOverwriter.py [-y | -n] (optional)
        -y: Ask the user which part of the file name is the artist and which part is the title.
        -n: Do not ask the user, just use the first and second parts of the file name as artist and title, respectively.
    this pertains to the tagger's expected file name format: "artist - title.ext"
"""


def get_file_name(file_path):
    name = os.path.basename(file_path)
    return name[:name.rfind('.')]


def get_file_extension(file_path):
    name = os.path.basename(file_path)
    return name[name.rfind('.') + 1:]


def get_artist_and_title_from_file_name(file_name, ask_user):
    parts = file_name.split(' - ')

    if len(parts) == 2 and not ask_user:
        return parts[0], parts[1]

    def get_part(part_name):
        print(f"which of the parts is the {part_name}?")
        for i, part in enumerate(parts):
            print("{}: {}".format(i + 1, part))

        while True:
            try:
                part_index = int(input())
                if part_index < 1 or part_index > len(parts):
                    raise ValueError
                break
            except ValueError:
                print("Invalid input!")

        return parts[part_index - 1]

    artist = get_part('artist')
    parts = [p for p in parts if p != artist]
    title = parts.pop() if len(parts) == 1 else get_part('title')

    return artist, title


def tag(file_path, ask_user=False):
    file_name = get_file_name(file_path)
    if ' - ' not in file_name:
        print('File name does not contain " - " and thus cannot be seperated into artist and title!')
        return False

    artist, title = get_artist_and_title_from_file_name(file_name, ask_user)
    if not artist or not title:
        print('Could not get artist and/or title!')
        return False

    file_extension = get_file_extension(file_path)

    file = EXTS[file_extension](file_path)
    if file is None:
        print('!!! ERROR: Could not open file: ' + file_path)
        return False

    file['artist'] = artist
    file['title'] = title

    file.save()
    print('==============================')
    print('Tagged: ' + file_path)
    print('------------------------------')
    print('\tArtist:\t' + artist)
    print('\tTitle:\t' + title)
    print('==============================')


def main():
    """
    list the files in current directory, asks the user to pick one, then tag it.
    :return:
    """
    ask_user = True

    if len(sys.argv) > 1:
        if sys.argv[1] == '-n':
            ask_user = False
        elif sys.argv[1] != '-y':
            return print(HELP_MSG)

    folder = os.getcwd()
    print('Current directory: ' + folder)

    files = []
    for file in os.listdir(folder):
        file_path = os.path.join(folder, file)
        if not os.path.isdir(file_path) and any(file.endswith(f".{ext}") for ext in EXTS):
            files.append(file_path)

    if not files:
        print(f"No {'/'.join(EXTS.keys())} files found in the current directory!")
        return

    def print_files():
        print('Files:')
        for i, file in enumerate(files):
            print('{}: {}'.format(i + 1, os.path.basename(file)))

    def filter_files(query):
        query = query.lower().strip()
        nonlocal files
        files = [file for file in files if query in os.path.basename(file).lower()]

    print_files()
    while True:
        try:
            inp = input('\nPick a file to tag by index, or type f:<query> to filter files: ')
            if inp.startswith('f:'):
                filter_files(inp[2:])
                print_files()
                continue
            
            file_index = int(inp)
            if file_index < 1 or file_index > len(files):
                raise ValueError
            break
        except ValueError:
            print('Invalid input!')

    file_path = os.path.join(folder, files[file_index - 1])
    tag(file_path, ask_user)


if __name__ == '__main__':
    main()
