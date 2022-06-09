import os
import mutagen
from mutagen.id3 import TPE1, TIT2
import sys


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
    title = (parts[0] if artist == parts[1] else parts[1]) if len(parts) == 2 else get_part('title')

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

    audio = mutagen.File(file_path)
    if audio is None:
        print('!!! ERROR: Could not open file: ' + file_path)
        return False

    file_extension = get_file_extension(file_path)
    if file_extension == 'mp3':
        if audio.tags is None:
            audio.add_tags()
        audio['TPE1'] = TPE1(text=artist)
        audio['TIT2'] = TIT2(text=title)
    elif file_extension == 'opus':
        audio['artist'] = artist
        audio['title'] = title

    audio.save()
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
            print("Supported arguments: -y, -n")

    folder = os.getcwd()
    print('Current directory: ' + folder)

    files = []
    for file in os.listdir(folder):
        file_path = os.path.join(folder, file)
        if not os.path.isdir(file_path) and file_path.endswith('.mp3') or file_path.endswith('.opus'):
            files.append(file_path)

    if not files:
        print("No mp3/opus files found!")
        return

    print('Files:')
    for i, file in enumerate(files):
        print('{}: {}'.format(i + 1, os.path.basename(file)))

    while True:
        try:
            file_index = int(input('\nPick a file to tag: '))
            if file_index < 1 or file_index > len(files):
                raise ValueError
            break
        except ValueError:
            print('Invalid index!')

    file_path = os.path.join(folder, files[file_index - 1])
    tag(file_path, ask_user)


if __name__ == '__main__':
    main()
