from string import ascii_uppercase, ascii_letters


class CaesarCipher:
    def __init__(self, shift: int):
        rot = ascii_uppercase[shift:] + ascii_uppercase[:shift]
        self.ENCODE_TABLE = str.maketrans(ascii_letters, rot + rot)
        self.DECODE_TABLE = str.maketrans(rot, ascii_uppercase)

    def encode(self, st: str) -> str:
        return st.translate(self.ENCODE_TABLE)

    def decode(self, st: str) -> str:
        return st.translate(self.DECODE_TABLE)
