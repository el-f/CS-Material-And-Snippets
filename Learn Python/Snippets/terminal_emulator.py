import platform
import subprocess
import time
import os
from collections import deque
from datetime import datetime
from itertools import cycle

is_windows = platform.system() == 'Windows'
prefixes = cycle(["$ ", f"{os.getcwd()} $ ", ])


class TerminalEmulator:
    COMMAND_NOT_FOUND = -1
    COMMAND_PROCESSED = 0
    COMMAND_ERROR = 1
    MULTIPLE_COMMAND_SPLITTER = '&'

    def __init__(self):
        self.history = []
        self.command_queue = deque()
        self.start_time = datetime.now()
        self.prefix = next(prefixes)
        self.my_commands = {
            '!help': (lambda command: self.help(command), "show all commands or use !help [command]"),
            'cd': (lambda command: os.chdir(''.join(command.split()[1:])), "change directory"),
            'history': (lambda command: self.process_history(command), "view and run history"),
            'exit': (lambda _: [print(f"Terminal ran for {datetime.now() - self.start_time}"
                                      f" and executed {len(self.history)} commands"), exit()],
                     "exit the terminal"),
            'mult': (lambda command: self.multiple_commands(command),
                     f"run multiple commands separated by '{self.MULTIPLE_COMMAND_SPLITTER}'"),
            'prefix': (lambda _: setattr(self, 'prefix', next(prefixes)), "Cycle between the prefixes"),
        }

    def process_history(self, command: str):
        if len(command.split()) == 2:
            self.history.pop(len(self.history) - 1)
            self.command_queue.append(self.history[int(command.split()[1])])
        else:
            print("run 'history x' to run the command in index x")
            [print(f"{i}) {x}") for i, x in enumerate(self.history)]

    def process_custom_cmd(self, command: str) -> int:
        if len(command) == 0:
            return self.COMMAND_ERROR

        command = command.lower()
        try:
            self.my_commands[command.split()[0]][0](command)
            return self.COMMAND_PROCESSED

        except KeyError:
            return self.COMMAND_NOT_FOUND

        except Exception as e:
            print(e)
            return self.COMMAND_ERROR

    def process_cmd(self):
        command = self.command_queue.pop()
        self.history.append(command)
        process_match_result = self.process_custom_cmd(command)

        if process_match_result >= 0:
            return

        if subprocess.call(["cmd", "/c", command] if is_windows else [command]) == 1:
            time.sleep(0.1)

    def run(self):
        print("############################")
        print("### My Terminal Emulator ###")
        print("### run '!help' for help ###")
        print("############################")
        while True:
            if len(self.command_queue) == 0:
                cmd = input(self.prefix)
                self.command_queue.append(cmd)
            self.process_cmd()

    def multiple_commands(self, command: str):
        cmd = command.split()
        if len(cmd) < 2:
            raise RuntimeError("Missing Arguments!")
        cmd = ' '.join(cmd[1:])
        for command in reversed(cmd.split(self.MULTIPLE_COMMAND_SPLITTER)):
            if command == 'history':
                raise RuntimeError("it is forbidden to chain the history command!")

            self.command_queue.append(command)

    def help(self, command: str):
        cmd = command.split()
        if len(cmd) == 2:
            try:
                print(f"{cmd[1]} \t {self.my_commands[cmd[1]][1]}")
            except KeyError:
                print("No such custom command!")
        else:
            c_title = "COMMAND"
            d_title = "DESCRIPTION"
            set_len = 14
            print("For more information on a specific command, type !HELP command-name")
            print(f"{c_title}{(set_len - len(c_title)) * ' '} {d_title}")
            print("-" * (len(c_title + d_title) + set_len + 1))
            for k in self.my_commands.keys():
                print(f"{k}{' ' * (set_len - len(k))} {self.my_commands[k][1]}")


if __name__ == '__main__':
    TerminalEmulator().run()
