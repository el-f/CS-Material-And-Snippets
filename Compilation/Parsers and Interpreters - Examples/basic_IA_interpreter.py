from ast import parse, Expr, Assign, BinOp, Name, Num
from operator import add, sub, mul, mod, truediv
from collections import OrderedDict
import operator
import re


class Interpreter:

    def __init__(self):
        self.vars = {}

    def input(self, expression):

        op = {'Sub': sub, 'Add': add, 'Mult': mul, 'Div': truediv, 'Mod': mod}

        def _eval(node):

            if isinstance(node, Expr):
                return _eval(node.value)
            if isinstance(node, Name):
                return self.vars[node.id]
            if isinstance(node, Num):
                return node.n
            if isinstance(node, BinOp):
                return op[type(node.op).__name__](_eval(node.left), _eval(node.right))
            if isinstance(node, Assign):
                name = node.targets[0].id
                self.vars[name] = _eval(node.value)
                return self.vars[name]

        tree = parse(expression)
        return _eval(tree.body[0]) if len(tree.body) else ''


# ***********************
# *  without builtins   *
# ***********************

def tokenize(expression):
    regex = re.compile(r"\s*(=>|[-+*/%=()]|[A-Za-z_]\w*|\d*\.?\d+)\s*")
    tokens = regex.findall(expression)
    return [s for s in tokens if not s.isspace()]


def split_list(lst, item):
    if item not in lst: return lst

    i = lst.index(item)
    return lst[0:i], lst[i + 1:]


class InterpreterV2:
    operators = OrderedDict(
        {'*': operator.mul, '/': operator.truediv, '%': operator.mod,
         '+': operator.add, '-': operator.sub}
    )

    def __init__(self):
        self.vars = {}
        self.functions = {}

    def input(self, expression):
        tokens = tokenize(expression)

        if '=' in tokens:
            left, right = split_list(tokens, '=')
            value = self.calc_expression(right)
            self.vars[left[0]] = value
            return value
        else:
            return self.calc_expression(tokens)

    def calc_expression(self, tokens):
        if not tokens: return ''
        if len(tokens) == 1:
            value = tokens[0]
            if self.is_number(value):
                return int(value)
            elif self.is_var(value):
                return self.vars[value]

        while '(' in tokens:
            opened = 0
            closed = 0

            i = tokens.index('(')
            for j, t in enumerate(tokens):
                if t == '(': opened += 1
                if t == ')': closed += 1
                if opened and opened == closed:
                    value = self.calc_expression(tokens[i + 1:j])
                    tokens = tokens[0:i] + [str(value)] + tokens[j + 1:]
                    break

        for o in self.operators:
            if o in tokens:
                left, right = split_list(tokens, o)
                left, right = self.calc_expression(left), self.calc_expression(right)
                return self.operators[o](left, right)

        raise ValueError('Bad input')

    @staticmethod
    def is_number(token):
        return bool(re.match(r'^\d+$', token))

    @staticmethod
    def is_var(token):
        return bool(re.match(r'^\w+$', token))


# ----------------------------------------------------------------------------------------------------------------------
# ****************************
# ********* Tests ************
# ****************************
# ----------------------------------------------------------------------------------------------------------------------


def basic_ia_interpreter_tests(subject_interpreter):
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


if __name__ == '__main__':
    basic_ia_interpreter_tests(Interpreter)
    print("\nInterpreter: ALL TESTS PASSED")
    print("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")
    basic_ia_interpreter_tests(InterpreterV2)
    print("\nInterpreterV2: ALL TESTS PASSED")
