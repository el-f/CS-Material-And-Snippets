import re

def solve_runes(runes):
    found_digits = {int(c) for c in runes if c.isdigit()}
    runes = runes.replace("=", "==")
    for digit in range(10):
        if digit in found_digits:               continue
        curr = runes.replace("?", str(digit))
        if re.search("^0\d|[^\d]0\d", curr):    continue
        if eval(curr):                          return digit
    return -1