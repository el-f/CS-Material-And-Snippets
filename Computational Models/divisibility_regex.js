/*
 * Regular expressions for determining divisibility by a particular number.
 *
 * Robin Houston, November 2010
 *
 * https://s3.boskent.com/divisibility-regex/divisibility-regex.html
 */

/*
 * We'll support numbers up to base 36, because that means we can
 * use the numerals 0-9 and the letters a-z as digits.
 */
var digits = "0123456789abcdefghijklmnopqrstuvwxyz";

/**
 * Spawn a new object, with the specified prototype.
 */
function spawn(proto) {
    var Constructor = function () {
    };
    Constructor.prototype = proto;
    return new Constructor();
}


/* Simple object representation of regular expressions.
 * This means we can pretty-print the expressions in an economical way,
 * which is hard to do if we represent the regular expressions as strings throughout,
 * and (more importantly) that we can apply some simplifications.
 *
 * Types are:
 *  - E, the trivial "epsilon" expression that matches only the empty string,
 *  - C, a character constant,
 *  - S, a Kleene star of a regular expression,
 *  - A, an alternation (disjunction) of regular expressions,
 *  - L, a concatenation of regular expressions ('L' is for List).
 *
 * We maintain these invariants:
 *  - A List never contains other Lists;
 *  - An Alternation never contains other Alternations.
 *
 * All these objects should be treated as immutable externally,
 * though they are mutated by the simplify() method.
 *
 * There is an option to simplify the regular expressions
 * by applying meaning-preserving local rewrite rules.
 * The rewrite rules we use are:
 *
 *  XX* -> X+
 *  X|Y+X -> Y*X
 *  (X*Y)*X* -> (X|Y)*
 *
 * These two simple rules suffice to dramatically simplify
 * many of the long regular expressions that arise.
 */

function re_equal(a, b) {
    return a.toString() === b.toString();
}

function E() {
    return {
        "type": "E",
        "toString": function (atomic) {
            return "";
        },
        "is_plus": false,
        "_val": function () {
            return undefined;
        },
        "simplify": function () {
            return this;
        }
    };
}

function C(c) {
    if (c.length != 1) {
        throw "C: not a single character";
    }
    return {
        "type": "C",
        "toString": function (atomic) {
            if (0 <= "\\()[]{}+*?".indexOf(c)) {
                return "\\" + c;
            } else {
                return c;
            }
        },
        "_val": function () {
            return c;
        },
        "simplify": function () {
            return this;
        }
    };
}

function S(re, is_plus) {
    if (re.type === "S" || re.type === "E") {
        re.is_plus = re.is_plus && is_plus;
        return re;
    }
    return {
        "type": "S",
        "toString": function (atomic) {
            return re.toString(true) + (this.is_plus ? "+" : "*");
        },
        "is_plus": is_plus,
        "_val": function () {
            return re;
        },
        "simplify": function () {
            return S(re.simplify(), is_plus);
        }
    };
};

function A() {
    if (arguments.length == 0) {
        return E();
    }
    if (arguments.length == 1) {
        return arguments[0];
    }

    var res = [];
    for (var i = 0; i < arguments.length; i++) {
        var re = arguments[i];
        if (re.type === "A") {
            [].push.apply(res, re._val());
        } else {
            res.push(re);
        }
    }

    /*
     * This (commented-out) version of the character_class function
     * uses character ranges where possible, e.g. [0-46-9]
     *
     * I'm not convinced the result is any clearer, which is
     * the only reason it's disabled.

    var character_class = function(chars) {
      chars.sort();
      var ret = "";
      var this_contig = "";
      for (var i = 0; i < chars.length; i++) {
        this_contig += chars[i];
        if (i + 1 == chars.length || chars[i+1].charCodeAt(0) != chars[i].charCodeAt(0) + 1) {
          if (this_contig.length > 3) {
            ret += this_contig.charAt(0) + "-" + this_contig.charAt(this_contig.length - 1);
          } else {
            ret += this_contig;
          }
          this_contig = "";
        }
      }
      ret += this_contig;
      return "[" + ret + "]";
    };
    */

    var character_class = function (chars) {
        chars.sort();
        return "[" + chars.join("") + "]";
    };

    return {
        "type": "A",
        "toString": function (atomic) {
            var disjuncts = [];
            var num_init_chars = 0;
            var found_non_char = false;

            for (var i = 0; i < res.length; i++) {
                if (!found_non_char && res[i].type == 'C') {
                    num_init_chars++;
                } else {
                    found_non_char = true;
                }
                disjuncts.push(res[i].toString(false));
            }
            if (!found_non_char) {
                // All the disjuncts are single characters: output a character class
                return character_class(disjuncts);
            }

            var ret;
            if (num_init_chars > 2) {
                ret = character_class(disjuncts.slice(0, num_init_chars)) + "|" + disjuncts.slice(num_init_chars).join("|");
            } else {
                ret = disjuncts.join("|");
            }
            return atomic ? "(" + ret + ")" : ret;
        },
        "_val": function () {
            return res;
        },
        "simplify": function () {
            // X|Y+X -> Y*X
            var simplified_res = [];
            for (var i = 0; i < res.length; i++) {
                var this_re = res[i].simplify();

                if (simplified_res.length > 0 && this_re.type === 'L') {
                    var hd = this_re.hd();
                    var tail = this_re.tail();
                    if (hd.type === 'S' && hd.is_plus) {
                        if (re_equal(A.apply(null, simplified_res.slice(0, simplified_res.length)), tail)) {
                            simplified_res = [L(S(hd._val()), tail).simplify()];
                            continue;
                        }
                    }
                }
                simplified_res.push(this_re);
            }
            return A.apply(null, simplified_res);
        }
    };
};

function L() {
    var res = [];
    for (var i = 0; i < arguments.length; i++) {
        var re = arguments[i];
        if (re.type === "E") {
            // do nothing
        } else if (re.type === "L") {
            [].push.apply(res, re._val());
        } else {
            res.push(re);
        }
    }

    if (res.length == 0) {
        return E();
    }
    if (res.length == 1) {
        return res[0];
    }

    return {
        "type": "L",
        "toString": function (atomic) {
            var ret = "";
            for (var i = 0; i < res.length; i++) {
                ret += res[i].toString(true);
            }
            if (atomic) {
                return "(" + ret + ")";
            } else {
                return ret;
            }
        },
        "_val": function () {
            return res;
        },
        "simplify": function () {
            var simplified_res = [];
            for (var i = 0; i < res.length; i++) {
                var this_re = res[i].simplify();

                if (simplified_res.length > 0) {
                    if (this_re.type == "S" && !this_re.is_plus) {
                        var previous_re = L.apply(null, simplified_res);

                        if (re_equal(this_re._val(), previous_re)) {
                            // XX* -> X+
                            simplified_res = [S(this_re._val(), true)];
                            continue;
                        }

                        if (previous_re.type == 'S' && previous_re._val().type == 'L') {
                            var prev_hd = previous_re._val().hd();
                            if (prev_hd.type == 'S' && !prev_hd.is_plus) {
                                if (re_equal(prev_hd._val(), this_re._val())) {
                                    // (X*Y)*X* -> (X|Y)*
                                    simplified_res[simplified_res.length - 1] = S(A(this_re._val(), previous_re._val().tail()));
                                    continue
                                }
                            }
                        }
                    }
                }
                simplified_res.push(this_re);
            }
            return L.apply(null, simplified_res);
        },
        "hd": function () {
            return res[0];
        },
        "tail": function () {
            return L.apply(null, res.slice(1));
        }
    };
}

/* Object representation of deterministic finite automata.
 * Each transition is labelled with a regular expression object.
 */

/**
 * Prototype object for DFAs.
 */
var DFA = {
    "create": function () {
        var dfa = spawn(DFA);
        dfa.states = {};
        dfa.transitions = {};
        dfa.transitions_reversed = {};
        return dfa;
    },

    "addState": function (state) {
        if (this.states[state])
            throw "addState: This state (" + state + ") already exists in the DFA";
        this.states[state] = true;
    },

    "addTransition": function (from_state, to_state, transitionRegex) {
        if (!this.states[from_state])
            throw "addTransition: This state (" + from_state + ") does not exist in the DFA";
        if (!this.states[to_state])
            throw "addTransition: This state (" + to_state + ") does not exist in the DFA";

        if (!this.transitions[from_state]) {
            this.transitions[from_state] = {};
        }
        if (this.transitions[from_state][to_state]) {
            this.transitions[from_state][to_state] = A(this.transitions[from_state][to_state], transitionRegex);
        } else {
            this.transitions[from_state][to_state] = transitionRegex;
        }

        if (!this.transitions_reversed[to_state]) {
            this.transitions_reversed[to_state] = {};
        }
        this.transitions_reversed[to_state][from_state] = this.transitions[from_state][to_state];
    },

    "transitionRegex": function (from_state, to_state, parenthesize, star) {
        if (!this.states[from_state])
            throw "transitionRegex: This state (" + from_state + ") does not exist in the DFA";
        if (!this.states[to_state])
            throw "transitionRegex: This state (" + to_state + ") does not exist in the DFA";

        if (typeof (this.transitions[from_state]) === "undefined")
            return E();
        if (typeof (this.transitions[from_state][to_state]) === "undefined")
            return E();

        if (from_state === to_state) {
            return S(this.transitions[from_state][to_state]);
        }
        return this.transitions[from_state][to_state];
    },

    "eliminateState": function (state) {
        if (!this.states[state])
            throw "eliminateState: This state (" + state + ") does not exist in the DFA";

        for (var from_state in this.transitions_reversed[state]) {
            if (from_state == state)
                continue;
            for (var to_state in this.transitions[state]) {
                if (to_state == state)
                    continue;
                this.addTransition(
                    from_state, to_state, L(
                        this.transitionRegex(from_state, state, true),
                        S(this.transitionRegex(state, state, true)),
                        this.transitionRegex(state, to_state, true)
                    )
                );
            }
        }

        // Now delete the state and all its transitions
        for (var from_state in this.transitions_reversed[state]) {
            if (typeof (this.transitions[from_state]) !== "undefined") {
                delete this.transitions[from_state][state];
            }
        }
        for (var to_state in this.transitions[state]) {
            if (typeof (this.transitions_reversed[to_state]) !== "undefined") {
                delete this.transitions_reversed[to_state][state];
            }
        }

        delete this.transitions[state];
        delete this.transitions_reversed[state];
        delete this.states[state];
    }
};

/**
 * Generate a DFA that takes a string representation of a number in base `base'
 * that computes its numeric value modulo `modulus'.
 */
function modular_dfa(base, modulus) {
    if (base < 2 || base > digits.length) {
        throw "base (" + base + ") is out of range";
    }

    var dfa = DFA.create();
    for (var i = 0; i < modulus; i++) {
        dfa.addState(i);
    }
    for (var i = 0; i < modulus; i++) {
        for (var j = 0; j < base; j++) {
            dfa.addTransition(i, (i * base + j) % modulus, C(digits.charAt(j)));
        }
    }

    return dfa;
}

/**
 * Generate a regular expression that matches only multiples
 * of `divisor', when expressed in base `base'.
 */
function divisibility_regex(base, divisor, simplify) {
    var dfa = modular_dfa(base, divisor);
    for (var i = 1; i < divisor; i++) {
        dfa.eliminateState(i);
    }
    var regex = dfa.transitionRegex(0, 0);
    if (simplify) {
        regex = regex.simplify();
    }
    return regex.toString(false);
}
