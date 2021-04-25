# Fill in the functions content & think about the return values. (Don't forget to remove the 'pass' statement)
# In questions with classes you can create the class & write the logic inside the function.

# Iterator template to eliminate code duplication:
class MyIterator:
    def __init__(self):  # add parameters
        self.arr = []
        self.current_index = -1

    def __iter__(self):
        return self

    def __next__(self):
        self.current_index += 1

        if self.current_index >= len(self.arr):
            raise StopIteration

        return self.arr[self.current_index]


# Class
def q1a(_input_num):
    class PrimeSmallerThan(MyIterator):
        def __init__(self):  # add parameters
            super().__init__()
            self.arr = [x for x in range(2, _input_num + 1) if all(x % y != 0 for y in range(2, int(x ** 0.5) + 1))]

    instance = PrimeSmallerThan()  # add parameters
    return instance


# Generator (using generator comprehension)
def q1b(_input_num):
    return (x for x in range(2, _input_num + 1) if all(x % y != 0 for y in range(2, int(x ** 0.5) + 1)))


# List comprehension
def q2(n):
    return [x for x in range(2, n // 2 + 1) if n % x == 0]


# One line
# m - min, n - max
def q3(m, n):
    return ["prime" if all(x % y != 0 for y in range(2, int(x ** 0.5) + 1)) else "not prime" for x in range(m, n + 1)]


# Generator (using generator comprehension)
# m - min, n - max
# I decided to include numbers that end with zero since technically x * 0 = 0 is a valid multiplication result.
def q4(m, n):
    return (x for x in range(m, n + 1) if x % 2 == 0 and (x % 10) % ((x // 10) % 10) == 0)


# One line
def q5(_str: str):
    return {char: _str.count(char) for char in _str}


# Generator (using generator comprehension)
def q6a(str1: str, str2: str):
    return (str1[j] for j in range(len(str1)) if str1[j] == str2[j])


# Class
def q6b(str1, str2):
    class StringsCompare(MyIterator):  # add class functions
        def __init__(self):  # add parameters
            super().__init__()
            self.arr = [str1[j] for j in range(len(str1)) if str1[j] == str2[j]]

    instance = StringsCompare()  # add parameters
    return instance


# One line
def q7(char_list, index_list):
    return ''.join(char_list[j - 1] for j in index_list)


# Generator
def q8a(a, b):
    mode = 'U'  # 'U' = counting up, 'D' - counting down
    lower, upper = min(a, b), max(a, b)
    number = lower
    while True:
        cur = number
        if mode == 'U':
            number += 1
            if number == upper:
                mode = 'D'
        else:
            number -= 1
            if number == lower:
                mode = 'U'
        yield cur


# q8a with user_choice
# I added debug prints for easier understanding of the function behavior.
def q8b(a, b):
    lower, upper = min(a, b), max(a, b)
    number = lower
    mode = 'U'
    while True:
        user_choice = yield number

        if user_choice is not None:
            print(f"choosing dir based on user choice: {user_choice}")
            mode = 'U' if int(user_choice) >= 0 else 'D'

        if mode == 'U':
            number += 1
            if number >= upper:
                print("got to the upper edge! changing direction!")
                mode = 'D'
                number = min(upper, number)
        else:
            number -= 1
            if number <= lower:
                print("got to the lower edge! changing direction!")
                mode = 'U'
                number = max(lower, number)


# Remove the '#' to run the corresponding test
# Don't forget to fill in the parameters.
if __name__ == "__main__":
    # q1a #
    input_num = 100
    for num in q1a(input_num):
        print(num, end=" ")
    print()

    # q1b #
    for num in q1b(100):
        print(num, end=" ")
    print()

    # q2 #
    print(q2(24))

    # q3 #
    print(q3(2, 14))

    # q4 #
    for c in q4(12, 45):
        print(c, end=" ")
    print()

    # q5 #
    print(q5("this is a simple string"))

    # q6a #
    for c in q6a("like", "love"):
        print(c, end=" ")
    print()

    # q6b #
    for c in q6b("like", "love"):
        print(c, end=" ")
    print()

    # q7 #
    print(q7(['a', 'h', 'f', 'e', 'y', 'u'], [1, 5, 3, 6, 2, 4]))

    # q8a #
    g = q8a(3, 11)
    for i in range(30):
        print(next(g), end=" ")
    print()

    # q8b #
    g2 = q8b(3, 11)
    for i in range(5):
        print(next(g2))
    print(g2.send(-1))
    for i in range(15):
        print(next(g2))
    print(g2.send(1))
    for i in range(5):
        print(next(g2))
