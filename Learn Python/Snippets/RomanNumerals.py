# Convert Integer up to a 1000 to a roman numeral
def convert(num):
    if num <= 1000:
        # create dict of integer to roman digits mapping
        roman_dict = {
            1000: 'M',
            900: 'CM',
            500: 'D',
            400: 'CD',
            100: 'C',
            90: 'XC',
            50: 'L',
            40: 'XL',
            10: 'X',
            9: 'IX',
            5: 'V',
            4: 'IV',
            1: 'I',
        }

        result = ""
        for key in roman_dict.keys():
            case_occurrences = num // key
            if case_occurrences >= 1:
                result += roman_dict[key] * case_occurrences
                num -= case_occurrences * key
        return result

    else:
        return None


print(convert(928))  # CMXXVIII
print(convert(124))  # CXXIV
print(convert(239))  # CCXXXIX
print(convert(3))