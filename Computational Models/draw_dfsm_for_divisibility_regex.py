import pygraphviz as pgv
from pprint import pprint
from random import choice as rchoice


def baseN(n, b, syms="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"):
    """ converts a number `n` into base `b` string """
    return ((n == 0) and syms[0]) or (baseN(n // b, b, syms).lstrip(syms[0]) + syms[n % b])


def divided_by_N(number, base):
    """
    constructs DFA that accepts given `base` number strings
    those are divisible by a given `number`
    """
    ACCEPTING_STATE = START_STATE = '0'
    SYMBOL_0 = '0'
    dfa = {
        str(from_state): {
            str(symbol): 'to_state' for symbol in range(base)
        }
        for from_state in range(number)
    }
    dfa[START_STATE][SYMBOL_0] = ACCEPTING_STATE
    # `lookup_table` keeps track: 'number string' -->[dfa]--> 'end_state'
    lookup_table = {SYMBOL_0: ACCEPTING_STATE}.setdefault
    for num in range(number * base):
        end_state = str(num % number)
        num_s = baseN(num, base)
        before_end_state = lookup_table(num_s[:-1], START_STATE)
        dfa[before_end_state][num_s[-1]] = end_state
        lookup_table(num_s, end_state)
    return dfa


def symcolrhexcodes(symbols):
    """
    returns dict of color codes mapped with alphabets symbol in symbols
    """
    return {
        symbol: '#' + ''.join([
            rchoice("8A6C2B590D1F4E37") for _ in "FFFFFF"
        ])
        for symbol in symbols
    }


def draw_transition_graph(dfa, filename="filename"):
    ACCEPTING_STATE = START_STATE = '0'
    colors = symcolrhexcodes(dfa[START_STATE].keys())
    # draw transition graph
    tg = pgv.AGraph(strict=False, directed=True, decorate=True)
    for from_state in dfa:
        for symbol, to_state in dfa[from_state].items():
            tg.add_edge("Q%s" % from_state, "Q%s" % to_state,
                        label=symbol, color=colors[symbol],
                        fontcolor=colors[symbol])

    # add intial edge from an invisible node!
    tg.add_node('null', shape='plaintext', label='start')
    tg.add_edge('null', "Q%s" % START_STATE, )

    # make end acception state as 'doublecircle'
    tg.get_node("Q%s" % ACCEPTING_STATE).attr['shape'] = 'doublecircle'
    tg.draw(filename, prog='circo')
    tg.close()


def print_transition_table(dfa):
    print("DFA accepting number string in base '%(base)s' "
          "those are divisible by '%(number)s':" % {
              'base': len(dfa['0']),
              'number': len(dfa), })
    pprint(dfa)


if __name__ == "__main__":
    number = int(input("Enter NUMBER: "))
    base = int(input("Enter BASE of number system: "))
    dfa = divided_by_N(number, base)

    print_transition_table(dfa)
    draw_transition_graph(dfa, filename=f"n_{number}_b_{base}_graph.png")
