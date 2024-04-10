
import sys
import os
import re
import shutil
import tqdm


def contains(source_file, target_file):
    """
    check if source_file starts with target_file, ignoring white spaces, _ and case sensitivity.
    source_file name can be multiple names separated by 'aka'
    """
    for name in target_file.lower().split("aka"):
        if re.sub(r'[\s_]', '', name).lower() in re.sub(r'[\s_]', '', source_file).lower():
            return True


def main():
    if len(sys.argv) != 2:
        print("Usage: python placer.py <target directory>")
        return

    source = os.getcwd()
    target = sys.argv[1]

    source_files = os.listdir(source)
    target_files = os.listdir(target)

    moved = 0

    with tqdm.tqdm(total=len(source_files)) as pbar:
        for source_file in source_files:
            for target_file in target_files:
                if contains(source_file, target_file):
                    source_file_full_path = os.path.join(source, source_file)
                    target_file_full_path = os.path.join(target, target_file)

                    shutil.move(source_file_full_path, target_file_full_path)

                    pbar.write(f"✅\t{source_file} was moved to {target_file}")

                    moved += 1
            pbar.update(1)

    print(f"----------- Summary -----------")
    print(f"Done! - moved {moved} files out of {len(source_files)}.")


if __name__ == "__main__":
    main()
