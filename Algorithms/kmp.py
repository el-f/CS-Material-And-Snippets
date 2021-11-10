class KMP:
    class OneIndexedString:
        def __init__(self, s):
            self.s = s

        def __getitem__(self, i):
            return self.s[i - 1]

    def __init__(self, pattern):
        self.pattern = self.OneIndexedString(pattern)
        self.m = len(pattern)
        self.states = [0] * (self.m + 1)
        self.set_states()

    def set_states(self):
        for i in range(1, self.m):
            self.states[i + 1] = self.delta(self.states[i], self.pattern[i + 1])

    def delta(self, state_i, c):
        if c == self.pattern[state_i + 1]:
            return state_i + 1
        if state_i == 0:
            return 0
        return self.delta(self.states[state_i], c)

    def search(self, text):
        t = self.OneIndexedString(text)
        positions_found = []
        state = 0
        for i in range(1, len(text) + 1):
            state = self.delta(state, t[i])
            if state == self.m:
                state = self.states[self.m]
                positions_found.append(i - self.m)

        return positions_found


if __name__ == '__main__':
    kmp = KMP("abc")
    print(kmp.search("abcdabcde"))
    print(kmp.search("abcabcabcabc"))

