from itertools import cycle


class VigenereCipher(object):
    def __init__(self, key, alphabet):
        self.key = key
        self.alphabet = alphabet

    def cipher(self, mode, _str):
        return ''.join(
            self.alphabet[(self.alphabet.index(m) + mode * self.alphabet.index(k)) % len(self.alphabet)]
            if m in self.alphabet else m for m, k in zip(_str, cycle(self.key))
        )

    def encode(self, _str): return self.cipher(1, _str)

    def decode(self, _str): return self.cipher(-1, _str)
