def solution(args):
    ns = ['-' if 1 <= i < len(args) - 1 and args[i - 1] == x - 1 and args[i + 1] == x + 1 else x
          for i, x in enumerate(args)]
    return ','.join(str(x) for i, x in enumerate(ns) if x != '-' or (i > 0 and ns[i - 1] != '-')).replace(',-,', '-')
