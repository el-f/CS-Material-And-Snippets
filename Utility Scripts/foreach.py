import sys
import os

def foreach():
    """
    for each file in the target directory, apply the command with the args.
    output is printed to the console.
    """
    if len(sys.argv) < 3:
        print("Usage: foreach.py <target_dir> <command> [<args>]")
        sys.exit(1)
        
    target_dir = sys.argv[1]
    command = sys.argv[2]
    args = sys.argv[3:]
    print(f"target_dir: {target_dir}", f"command: {command}", f"args: {args}", sep="\n")

    for file in os.listdir(target_dir):
        print(f"Processing {file}...")
        full_path = os.path.join(target_dir, file)
        os.system(f"{command} {' '.join(args)} \"{full_path}\"")
        print()
        
if __name__ == "__main__":
    foreach()
        
            