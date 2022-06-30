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
        {'*': operator.mul, '/': operator.div, '%': operator.mod,
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
