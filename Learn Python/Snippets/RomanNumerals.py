# Convert Integer up to a 1000 to a roman numeral
def convert(num):
    if num <= 1000:
        # create dict of integer to roman digits mapping
        roman_dict = {
            1: 'I',
            4: 'IV',
            5: 'V',
            9: 'IX',
            10: 'X',
            40: 'XV',
            50: 'L',
            90: 'XC',
            100: 'C',
            400: 'CD',
            500: 'D',
            900: 'CM',
            1000: 'M',
        }

        # create a list of all main cases in descending order
        cases = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]

        result = ""
        for case in cases:
            case_occurrences = num // case
            if case_occurrences >= 1:
                result += roman_dict[case] * case_occurrences
                num -= case_occurrences * case
        return result

    else:
        return None


print(convert(928))  # CMXXVIII
print(convert(124))  # CXXIV
print(convert(239))  # CCXXXIX
