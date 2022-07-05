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
            if any((sbj := v) in self.functions for v in vv): raise ValueError("Identifier already in use : " + sbj)

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


# ----------------------------------------------------------------------------------------------------------------------
# ****************************
# ********* Tests ************
# ****************************
# ----------------------------------------------------------------------------------------------------------------------

def ia_interpreter_tests(subject_interpreter):
    def assert_equals(actual, expected, message="FAILED"):
        if actual != expected:
            print(message)
            print("expected:", expected)
            print("actual:", actual)
            exit(1)

    def describe(message):
        print(message)

    def it(message):
        print(message)

    def expect_error(message, func):
        try:
            func()
        except Exception:
            return
        print(message)
        exit(1)

    describe("Basic Expression Evaluation")
    interpreter = subject_interpreter()

    it("Should handle empty input")
    assert_equals(interpreter.input(""), "", "input: ''")
    assert_equals(interpreter.input(" "), "", "input: ' '")

    it("Should echo constants")
    assert_equals(interpreter.input("9"), 9, "input: '9'")

    it("Should reject invalid input")
    expect_error("input: '1 2'", lambda: interpreter.input("1 2"))
    expect_error("input: '1two'", lambda: interpreter.input("1two"))

    it("Should handle addition")
    assert_equals(interpreter.input("1 + 1"), 2, "input: '1 + 1'")
    assert_equals(interpreter.input("2+2"), 4, "input: '2+2'")

    it("Should handle subtraction")
    assert_equals(interpreter.input("2 - 1"), 1, "input: '2 - 1'")
    assert_equals(interpreter.input("4-6"), -2, "input: '4-6'")

    it("Should handle multiplication")
    assert_equals(interpreter.input("2 * 3"), 6, "input: '2 * 3'")

    it("Should handle division")
    assert_equals(interpreter.input("8 / 4"), 2, "input: '8 / 4'")

    it("Should handle modulo")
    assert_equals(interpreter.input("7 % 4"), 3), "input: '7 % 4'"

    describe("Complex Expression Evaluation")
    interpreter = Interpreter()

    it("Should handle multiple operations")
    assert_equals(interpreter.input("4 + 2 * 3"), 10, "input: '4 + 2 * 3'")
    assert_equals(interpreter.input("4 / 2 * 3"), 6, "input: '4 / 2 * 3'")
    assert_equals(interpreter.input("7 % 2 * 8"), 8, "input: '7 % 2 * 8'")

    it("Should handle parentheses")
    assert_equals(interpreter.input("(4 + 2) * 3"), 18, "input: '(4 + 2) * 3'")
    assert_equals(interpreter.input("(7 + 3) / (2 * 2 + 1)"), 2, "input: '(7 + 3) / (2 * 2 + 1)'")

    it("Should handle nested parentheses")
    assert_equals(interpreter.input("(8 - (4 + 2)) * 3"), 6, "input: '(8 - (4 + 2)) * 3'")
    assert_equals(interpreter.input("(10 / (8 - (4 + 2))) * 3"), 15, "input: '(10 / (8 - (4 + 2))) * 3'")

    describe("Variables")
    interpreter = Interpreter()

    it("Should assign a constant to a variable")
    assert_equals(interpreter.input("x = 7"), 7, "input: 'x = 7'")

    it("Should read the value of a variable")
    assert_equals(interpreter.input("x"), 7, "input: 'x'")

    it("Should handle variables in expressions")
    assert_equals(interpreter.input("x + 3"), 10, "input: 'x + 3'")

    it("Should throw an error when variables don't exist")
    expect_error("input: 'y'", lambda: interpreter.input("y"))

    it("Should continue to function after an error is thrown")
    assert_equals(interpreter.input("y = x + 5"), 12, "input: 'y = x + 5'")
    assert_equals(interpreter.input("y"), 12, "input: 'y'")

    it("Should handle chained assignment")
    assert_equals(interpreter.input("x = y = 713"), 713, "input: 'x = y = 713'")
    assert_equals(interpreter.input("x"), 713, "input: 'x'")
    assert_equals(interpreter.input("y"), 713, "input: 'y'")

    it("Should handle nested assignment")
    assert_equals(interpreter.input("x = 29 + (y = 11)"), 40, "input: 'x = 29 + (y = 11)'")
    assert_equals(interpreter.input("x"), 40, "input: 'x'")
    assert_equals(interpreter.input("y"), 11, "input: 'y'")

    describe("Functions")
    interpreter = Interpreter()
    interpreter.input("x = 23")
    interpreter.input("y = 25")
    interpreter.input("z = 0")

    it("Should declare a valid function without error")
    assert_equals(interpreter.input("fn one => 1"), "", "input: 'fn one => 1'")
    assert_equals(interpreter.input("fn avg x y => (x + y) / 2"), "", "input: 'fn avg x y => (x + y) / 2'")
    assert_equals(interpreter.input("fn echo x => x"), "", "input: 'fn echo x => x'")

    it("Should throw an error when a function's expression contains invalid variable names")
    expect_error("input: 'fn add x y => x + z'", lambda: interpreter.input("fn add x y => x + z"))

    it("Should throw an error when a function's declaration includes duplicate variable names")
    expect_error("input: 'fn add x x => x + x'", lambda: interpreter.input("fn add x x => x + x"))

    it("Should throw an error when a function is declared within an expression")
    expect_error("input: '(fn f => 1)", lambda: interpreter.input("(fn f => 1)"))

    it("Should call a declared function")
    assert_equals(interpreter.input("one"), 1, "input: 'one'")
    assert_equals(interpreter.input("avg 4 2"), 3, "input: 'avg 4 2'")

    it("Should throw an error when a function is called with too few arguments")
    expect_error("input: 'avg 7'", lambda: interpreter.input("avg 7"))

    it("Should throw an error when a function is called with too many arguments")
    expect_error("input: 'avg 7 2 4'", lambda: interpreter.input("avg 7 2 4"))

    it("Should call chained functions")
    assert_equals(interpreter.input("avg echo 4 echo 2"), 3, "input: 'avg echo 4 echo 2'")

    it("Should throw an error when chained function calls result in too few arguments")
    expect_error("input: 'avg echo 7'", lambda: interpreter.input("avg echo 7"))

    it("Should throw an error when chained function calls result in too many arguments")
    expect_error("input: 'avg echo 7 echo 2 echo 4'", lambda: interpreter.input("avg echo 7 echo 2 echo 4"))

    it("Should parse nested functions")
    interpreter.input("fn f a b => a * b")
    interpreter.input("fn g a b c => a * b * c")
    assert_equals(interpreter.input("g g 1 2 3 f 4 5 f 6 7"), 5040, "input: 'g g 1 2 3 f 4 5 f 6 7'")

    describe("Conflicts")
    interpreter = Interpreter()
    interpreter.input("x = 0")
    interpreter.input("fn f => 1")

    it("Should throw an error when a function with the name of an existing variable is declared")
    expect_error("input: 'fn x => 0'", lambda: interpreter.input("fn x => 0"))

    it("Should throw an error when a variable with the name of an existing function is declared")
    expect_error("input: 'f = 5'", lambda: interpreter.input("f = 5"))

    it("Should overwrite an existing function")
    assert_equals(interpreter.input("f"), 1, "input: 'f'")
    interpreter.input("fn f => 0")
    assert_equals(interpreter.input("f"), 0, "input: 'f'")


if __name__ == '__main__':
    ia_interpreter_tests(Interpreter)
    print("\nALL TESTS PASSED!")
