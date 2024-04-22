
import sys
import os
import re
import shutil
import tqdm
from collections import defaultdict
import argparse

parser = argparse.ArgumentParser(description='Move files to folders based on their names.')
parser.add_argument('target', type=str, help='The target directory to move files to.')
parser.add_argument('--preview', '-p', action='store_true', help='Preview the moves without actually moving the files.')

def contains(source_file, target_file):
    """
    check if source_file starts with target_file, ignoring white spaces, _ and case sensitivity.
    source_file name can be multiple names separated by 'aka'
    """
    for name in target_file.lower().split("aka"):
        if re.sub(r'[\s_\.\-]', '', name).lower() in re.sub(r'[\s_\.\-]', '', source_file).lower():
            return True


def main():
    """
    for each file in current folder (source), check if there is a folder with a name such that
    the file name starts with that folder name. If there is, move the file to that folder.
    """
    args = parser.parse_args()
    is_preview = args.preview

    source = os.getcwd()
    target = args.target

    print(dict(is_preview=is_preview, source=source, target=target))

    source_files = os.listdir(source)
    target_files = os.listdir(target)

    moved = 0
    
    moves = defaultdict(list)

    for source_file in source_files:
        for target_file in target_files:
            if contains(source_file, target_file):
                moves[source_file].append(target_file)
                
    moves_with_one_target = {
        source_file: target_files[0]
        for source_file, target_files in moves.items()
        if len(target_files) == 1
    }
    
    for source_file, target_file in tqdm.tqdm(moves_with_one_target.items()):
        source_file_full_path = os.path.join(source, source_file)
        target_file_full_path = os.path.join(target, target_file)
        if is_preview:
            print(f"👀 Will move {source_file} to {target_file}")
        else:
            print(f"✅ Moved {source_file} to {target_file}")
            shutil.move(source_file_full_path, target_file_full_path)
        moved += 1

    print(f"----------- Summary -----------")
    if is_preview:
        print(f"Preview done! - {moved} files will be moved out of {len(source_files)}.")
    else:
        print(f"Done! - moved {moved} files out of {len(source_files)}.")


if __name__ == "__main__":
    main()
