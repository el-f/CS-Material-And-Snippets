def decodeBits(bits):
    import re

    # remove trailing and leading 0's
    bits = bits.strip('0')

    # find the least amount of occurrences of either a 0 or 1, and that is the time hop
    time_unit = min(len(m) for m in re.findall(r'1+|0+', bits))

    # hop through the bits and translate to morse
    return bits[::time_unit].replace('111', '-').replace('1', '.').replace('0000000', '   ').replace('000', ' ').replace('0', '')


def decodeMorse(morseCode):
    return ' '.join(''.join(MORSE_CODE[l] for l in w.split()) for w in morseCode.split('   '))


def decode_morse_v2(morse_code):
    morse_code = morse_code.strip().split('   ')
    morse_code = [m.split(' ') for m in morse_code]
    morse_code = [''.join([MORSE_CODE[c] for c in m]) for m in morse_code]
    return ' '.join(morse_code)


def decode_bits_v2(bits):
    import re
    bits = re.sub(r'(^(0*))|((0*)$)', '', bits)
    bits_min_length = min(len(b) for b in re.findall(r'1+|0+', bits))
    bits = re.sub(r'1{' + str(bits_min_length * 3) + '}', '-', bits)
    bits = re.sub(r'1{' + str(bits_min_length * 1) + '}', '.', bits)
    bits = re.sub(r'0{' + str(bits_min_length * 7) + '}', '   ', bits)
    bits = re.sub(r'0{' + str(bits_min_length * 3) + '}', ' ', bits)
    bits = re.sub(r'0{' + str(bits_min_length) + '}', '', bits)
    return bits


MORSE_CODE = {
    '.-': 'A', '-...': 'B', '-.-.': 'C', '-..': 'D', '.': 'E', '..-.': 'F',
    '--.': 'G', '....': 'H', '..': 'I', '.---': 'J', '-.-': 'K', '.-..': 'L',
    '--': 'M', '-.': 'N', '---': 'O', '.--.': 'P', '--.-': 'Q', '.-.': 'R',
    '...': 'S', '-': 'T', '..-': 'U', '...-': 'V', '.--': 'W', '-..-': 'X',
    '-.--': 'Y', '--..': 'Z',
    '-----': '0', '.----': '1', '..---': '2', '...--': '3', '....-': '4',
    '.....': '5', '-....': '6', '--...': '7', '---..': '8', '----.': '9',
    '.-.-.-': '.', '--..--': ',', '..--..': '?', '.----.': "'", '-.-.--': '!',
    '-..-.': '/', '-.--.': '(', '-.--.-': ')', '.-...': '&', '---...': ':',
    '-.-.-.': ';', '-...-': '=', '.-.-.': '+', '-....-': '-', '..--.-': '_',
    '.-..-.': '"', '...-..-': '$', '.--.-.': '@', '...---...': 'SOS'
}
