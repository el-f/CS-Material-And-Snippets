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
    part1 = file_name[:file_name.find(' - ')]
    part2 = file_name[file_name.find(' - ') + 3:]

    if not ask_user:
        return part1, part2

    # ask the user which of the parts is the artist and which is the title
    print("which of the parts is the artist?")
    print("1: " + part1)
    print("2: " + part2)
    while True:
        try:
            part_index = int(input())
            if part_index < 1 or part_index > 2:
                raise ValueError
            break
        except ValueError:
            print("Invalid input!")

    if part_index == 1:
        artist = part1
        title = part2
    else:
        artist = part2
        title = part1

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
    print('Tagged: ' + file_path)


def main():
    """
    list the files in current directory, asks the user to pick one, then tag it.
    :return:
    """
    ask_user = False

    if len(sys.argv) > 1:
        if sys.argv[1] == '-y':
            ask_user = True
        elif sys.argv[1] != '-n':
            print("Supported arguments: -y, -n")

    folder = os.getcwd()
    print('Current directory: ' + folder)

    files = []
    for file in os.listdir(folder):
        file_path = os.path.join(folder, file)
        if not os.path.isdir(file_path) and file_path.endswith('.mp3') or file_path.endswith('.opus'):
            files.append(file_path)

    print('Files:')
    for i, file in enumerate(files):
        print('{}: {}'.format(i + 1, file))

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
