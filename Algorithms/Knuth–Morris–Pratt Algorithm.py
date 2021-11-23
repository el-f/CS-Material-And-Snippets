class KMP:
    """
    Recursive implementation of KMP - better than than the dynamic programming version
    for real world use cases where character frequency is normally distributed!
    """

    def __init__(self, pattern):
        self.pattern = pattern
        self.m = len(pattern)
        self.states = [0] * (self.m + 1)
        self.set_states()

    def set_states(self):
        """
        Set the states of the FSM.
        """
        for i in range(1, self.m):
            self.states[i + 1] = self.delta(self.states[i], self.pattern[i])

    def delta(self, state_i, c):
        """
        The transition function `δ` from state to state.

        :param state_i: The current state of the FSM.
        :param c:       The char inputted to the FSM.
        :return:        The new state after the transition.
        """
        if c == self.pattern[state_i]:
            return state_i + 1
        if state_i == 0:
            return 0
        return self.delta(self.states[state_i], c)

    def search_in(self, text):
        """
        Search an input text for the pattern the KMP initialized to search for.

        :param text: input search text.
        :return:     list of positions the pattern was found at.
        """
        positions_found = []
        state = 0
        for i in range(0, len(text)):
            state = self.delta(state, text[i])
            if state == self.m:
                state = self.states[self.m]
                positions_found.append(i - self.m + 1)
        return positions_found


if __name__ == '__main__':
    search_abc = KMP("abc")
    print(search_abc.search_in("abcdabcde"))
    print(search_abc.search_in("abcabcabcabc"))

    search_ababc = KMP("abab")
    print(search_ababc.search_in("abababab"))
    print(search_ababc.search_in("aaababaabab"))
