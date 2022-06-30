import operator as op
import re
import string

RE = re.compile(r"\s*(=>|[-+*/%=()]|[A-Za-z_]\w*|\d*\.?\d+)\s*")

tokenize = lambda e: [s for s in RE.findall(e) if not s.isspace()]
is_ident = lambda t: t[0] in "_ " + string.ascii_letters


class Interpreter:
    def __init__(self):
        self.vars = {}
        self.functions = {}

    def input(self, expression):
        if "( fn " in ' '.join(tokenize(expression)): raise ValueError("Cannot declare function in an expression")

        while "(" in expression:
            if expression.startswith("fn "): break

            ptr = idx = expression.index("(")
            start, tofind = expression[:idx] if idx else "", 1
            while tofind:
                ptr += 1
                if expression[ptr] == ")": tofind -= 1
                if expression[ptr] == "(": tofind += 1

            expression = start + str(self.input(expression[idx + 1:ptr])) + expression[ptr + 1:]
        return self.parse(expression)

    def parse(self, expression):
        if expression.startswith("fn "):
            name, args, expr = expression.split()[1], expression.split("=>")[0].split()[2:], expression.split("=>")[
                1].strip()
            self.functions[name] = {"expr": expr, "args": args}

            if name in self.vars:
                raise ValueError("Name alreday in use " + name)
            elif len(args) > len(set(args)):
                raise ValueError("Repeated argument " + expression)
            elif any(t not in args and t not in self.functions for t in tokenize(expr) if is_ident(t)):
                raise ValueError("Invalid function" + expression)

            return ''

        # Deal with other expressions, find rightmost =
        left, expression = expression.rsplit("=", 1) if "=" in expression else ('', expression)
        tokens = tokenize(expression)
        if not tokens:
            return ''

        newtokens = []
        while tokens:
            token = tokens.pop()
            if is_ident(token):
                if token in self.functions:
                    args = {a: newtokens.pop() for a in self.functions[token]["args"]}
                    token = self.input(' '.join([args.get(t, t) for t in tokenize(self.functions[token]["expr"])]))
                elif token in self.vars:
                    token = self.vars[token]
                else:
                    raise ValueError("Referenced before assignment : " + token)

            newtokens.append(str(token))

        result = evaluate(' '.join(newtokens[::-1]))

        if left:
            vv = ' '.join(left.split()).split("=")
            if any(v in self.functions for v in vv): raise ValueError("Identifier already in use : " + v)

            for v in vv: self.vars[v.strip()] = result

        return result


def evaluate(s):
    OP = {"*": op.mul, "/": op.truediv, "+": op.add, "-": op.sub, "%": op.mod}

    tokens, stack, result = [w if w in OP else float(w) if '.' in w else int(w) for w in s.split()[::-1]], [], 0

    while tokens:
        t = tokens.pop()
        stack.append(OP[t](stack.pop(), tokens.pop()) if str(t) in '/*%' else t)
    while stack:
        n = stack.pop()
        result = OP[stack.pop() if stack else "+"](result, n)

    return result
