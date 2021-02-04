# Convert Integer up to a 1000 to a roman numeral
def convert(n):
    if n <= 1000:
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
        # create a  list of all the numbers in descending order
        arr = [1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000][::-1]
        # empty list for characters
        result = ""
        for i in arr:
            if n // i >= 1:
                result += roman_dict[i] * (n // i)
                n = n - (n // i) * i
        return result

    else:
        return None


print(convert(928))
print(convert(124))
print(convert(239))
