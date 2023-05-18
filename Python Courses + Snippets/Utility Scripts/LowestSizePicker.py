import os
import sys
import re
import shutil
import tqdm


def main():
    """
    Get input from the command line for a directory (referred to as 'target'). The current directory is considered
    the source directory. Proceed to examine all files in both the source and target directories, comparing them. If
    any files in the source directory have a corresponding file in the target directory (matching the name,
    but not necessarily the extension), check if the file in the target directory is larger than the one in the
    source directory. If it is, delete the file in the target directory and replace it with the file from the source
    directory.
    
    This is used as a utility for mainly after converting a bunch of files from one format to another,
    and you want to keep only the smallest size of each file. (my use case was converting from x264 to x265)
    """

    if len(sys.argv) != 2:
        print("Usage: python LowestSizePicker.py <target directory>")
        return

    source = os.getcwd()
    target = sys.argv[1]

    source_files = os.listdir(source)
    target_files = os.listdir(target)

    replaced = 0
    
    total_original_size = 0
    total_size_after_replacement = 0

    with tqdm.tqdm(total=len(source_files)) as pbar:
        for source_file in source_files:
            for target_file in target_files:
                if re.sub(r'\.[^.]*$', '', source_file) == re.sub(r'\.[^.]*$', '', target_file):
                    source_file_full_path = os.path.join(source, source_file)
                    target_file_full_path = os.path.join(target, target_file)

                    source_file_size = os.path.getsize(source_file_full_path)
                    target_file_size = os.path.getsize(target_file_full_path)
                    
                    total_original_size += source_file_size
                    total_size_after_replacement += min(source_file_size, target_file_size)

                    if source_file_size < target_file_size:
                        os.remove(target_file_full_path)

                        shutil.move(source_file_full_path, target)

                        pbar.write(
                            f"✅\t({round(target_file_size / source_file_size, 2) * 100:.2f}%)\t{target_file} was replaced "
                        )

                        replaced += 1
                    else:
                        pbar.write(
                            f"❌\t({round(target_file_size / source_file_size, 2) * 100:.2f}%)\t{target_file} was not replaced "
                        )
            pbar.update(1)

    print(f"----------- Summary -----------")
    print(f"Done! - replaced {replaced} files out of {len(target_files)}.")
    print(f"Total size before replacement: {total_original_size / 1024 ** 3:.3f} GB")
    print(f"Total size after replacement: {total_size_after_replacement / 1024 ** 3:.3f} GB")
    print(f"Total size saved: {(total_original_size - total_size_after_replacement) / 1024 ** 3:.3f} GB")
    print(f"Total target/source size ratio: {total_size_after_replacement / total_original_size * 100:.2f}%")
    
if __name__ == "__main__":
    main()
