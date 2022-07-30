# #############################################################################
# ############################# ENCODE / DECODE ###############################
# #############################################################################
from collections import Counter
from string import ascii_uppercase
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

    def encode(self, _str):
        return self.cipher(1, _str)

    def decode(self, _str):
        return self.cipher(-1, _str)


# #############################################################################
# ############################## CRACK THE KEY ################################
# #############################################################################

ALPHABET = ascii_uppercase
LETTER_FREQUENCY = {
    'A': 0.0815, 'B': 0.0144, 'C': 0.0276, 'D': 0.0379, 'E': 0.1311, 'F': 0.0292, 'G': 0.0199,
    'H': 0.0526, 'I': 0.0635, 'J': 0.0013, 'K': 0.0042, 'L': 0.0339, 'M': 0.0254, 'N': 0.0710,
    'O': 0.0800, 'P': 0.0198, 'Q': 0.0012, 'R': 0.0638, 'S': 0.0610, 'T': 0.1047, 'U': 0.0246,
    'V': 0.0092, 'W': 0.0154, 'X': 0.0017, 'Y': 0.0198, 'Z': 0.0008
}


def get_key(cipher_text, key_len):
    keyword = [find_key_for_group([cipher_text[letter] for letter in range(i, len(cipher_text), key_len)])
               for i in range(key_len)]
    return ''.join(keyword)


def find_key_for_group(group):
    blocks = [Counter(ALPHABET[ALPHABET.find(letter) - i]
                      for letter in group) for i in range(26)]
    chi_squared = [(index, sum(get_chi_squared(block, len(group))))
                   for index, block in enumerate(blocks)]
    return ALPHABET[min(chi_squared, key=lambda x: x[1])[0]]


def get_chi_squared(block, length):
    return [(block.get(letter, 0) - (length * LETTER_FREQUENCY[letter])) ** 2 / (length * LETTER_FREQUENCY[letter])
            for letter in ascii_uppercase]
