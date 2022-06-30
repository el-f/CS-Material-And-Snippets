import re


def tokenize(expr):
    if expr == "": return []
    regex = re.compile(r"\s*([\-+*/]|\d*\.?\d+)\s*")
    tokens = regex.findall(expr)
    return [s for s in tokens if not s.isspace()]


def calculate(expr):
    if re.match(r".*[^\d\-+*/.].*", expr): return "Error"
    tokens = tokenize(expr)
    num, op = [], None
    for token in tokens:
        if re.match(r"^\d*\.?\d+$", token):
            x = float(token)
            if op == '-':                   num.append(-x )
            elif op is None or op == '+':   num.append( x )
            elif op == '*':                 num[-1] *=  x
            else:                           num[-1] /=  x
            op = None
        else:                               op = token
    return sum(num)


if __name__ == '__main__':
    cases = (
        ("1.1", 1.1),                   # returns the number if no commands given
        ("10+5", 15),                   # addition
        ("8-2", 6),                     # subtraction
        ("4*3", 12),                    # multiplication
        ("18/2", 9),                    # division
        ("5+8-8*2/4", 9),               # multiple commands
        ("3x+1", "Error")               # handles incorrect input
    )
    for expr, result in cases:
        if calculate(expr) != result:
            print("Failed on {}".format(expr))
        else:
            print("Passed on {}".format(expr))
