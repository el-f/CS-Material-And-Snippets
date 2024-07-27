# find all duplicate videos in a directory and its subdirectories, by length, down to the millisecond
import os
import subprocess
import json
from collections import defaultdict
import tqdm

video_extensions = ['.mp4', '.mkv']

def get_length(filename):
    result = subprocess.check_output(
            f'ffprobe -v quiet -show_streams -select_streams v:0 -of json "{filename}"',
            shell=True).decode()
    fields = json.loads(result)['streams'][0]
    
    duration = fields.get('duration', None)
    frames   = fields.get('nb_frames', None)
    return duration, frames


def find_dups():
    seenDurs = defaultdict(list)
    seenFrames = defaultdict(list)
    
    num_files = sum([len(files) for _, _, files in os.walk(os.getcwd())])
    
    with tqdm.tqdm(total=num_files) as pbar:
        for root, dirs, files in os.walk(os.getcwd()):
            for file in files:
                if any(file.endswith(ext) for ext in video_extensions):
                    file_path = os.path.join(root, file)
                    length, frames = get_length(file_path)
                    if length:
                        seenDurs[length].append(file_path)
                    if frames:
                        seenFrames[frames].append(file_path)
                pbar.update(1)
                    
    print("Done!")   
    print("duplicates by duration:")         
    for length, files in seenDurs.items():
        if len(files) > 1:
            print(f"Length: {length}")
            for file in files:
                print(f"\t{file}")
            print("")
            
    print("-------------------------")
    print("duplicates by frames:")
    for frames, files in seenFrames.items():
        if len(files) > 1:
            print(f"Frames: {frames}")
            for file in files:
                print(f"\t{file}")
            print("")
            
if __name__ == '__main__':
    find_dups()
    
