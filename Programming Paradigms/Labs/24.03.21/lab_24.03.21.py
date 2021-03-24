def is_palindrome(string) -> bool:
    return string == string[::-1]


def easy_filter():
    print([i for i in range(2000, 3201) if (i % 7 == 0) and (i % 5 != 0)])


vowels = "aeiou"


def encrypt(string) -> str:
    return ''.join([char * 2 if char.lower() not in vowels else char for char in string])


def decrypt(string) -> str:
    result = ""
    i = 0
    while i < len(string):
        result += string[i]
        if string[i] not in vowels:
            i += 1
        i += 1
    return result


def recursive_bs(step):
    if step == 0:
        return
    print(f"{step} bottles of beer on the wall, {step} bottles of beer.\n"
          f"Take one down, pass it around, {step - 1} bottles of beer on the wall.")
    recursive_bs(step - 1)


def longest_string(_list: list) -> str:
    longest = ""
    for item in _list:
        current_str = item if not isinstance(item, list) else longest_string(item)
        if len(current_str) > len(longest):
            longest = current_str
    return longest


def lengths(_list):
    return [len(w) for w in _list]


def concat(list1, list2):
    return [w1 + w2 for w1 in list1 for w2 in list2]


def concat_zip_version(list1, list2):
    return [w1 + w2 for w1, w2 in zip(list1, list2)]


def twoLetterSubs(arr):
    return sum([[word[i:i + 2] for i in range(len(word) - 1)] for word in arr], [])


def twoLetterSubs_V2(arr):
    return [word[i:i + 2] for word in arr for i in range(len(word) - 1)]


if __name__ == '__main__':
    is_palindrome("racecar")
    easy_filter()
    print(encrypt("this is so fun"))
    print(decrypt("tthhiss  iss  sso  ffunn"))
    # recursive_bs(99)

    strings = ["wow", "this", "is", "so", ["easy", "long_ass_word"], ["hmmm"], "lol"]
    print(longest_string(strings))

    print(lengths(strings[:4]))
    l1 = ["a", "b", "c"]
    l2 = ["1", "2", "3", "4"]
    print(concat(l1, l2))
    print(concat_zip_version(l1, l2))
    print(twoLetterSubs(['hello', 'world']))
    print(twoLetterSubs_V2(['hello', 'world']))
