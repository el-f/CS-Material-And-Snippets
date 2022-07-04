#  51e056fe544cf36c410000fb

from collections import Counter
import re

pattern = "('*[A-Za-z]+'*)+"


def top_three_words(string: str):
    string = re.sub(r'[^A-Za-z\' ]+', ' ', string)
    d = Counter([x for x in string.split() if re.fullmatch(pattern, x)]).most_common()
    result = []
    index = 0
    while len(result) < 3 and index < len(d):
        current = d[index][0].lower()
        if current not in result:
            result.append(current)
        index += 1

    return result


def top_3_words(text):
    c = Counter(re.findall(r"[a-z']+", re.sub(r" '+ ", " ", text.lower())))
    return [w for w,_ in c.most_common(3)]


if __name__ == '__main__':
    assert top_three_words("""In a village of La Mancha, the name of which I have no desire to call to
            mind, there lived not long since one of those gentlemen that keep a lance
            in the lance-rack, an old buckler, a lean hack, and a greyhound for
            coursing. An olla of rather more beef than mutton, a salad on most
            nights, scraps on Saturdays, lentils on Fridays, and a pigeon or so extra
            on Sundays, made away with three-quarters of his income.""") == ["a", "of", "on"]
    assert top_three_words("a a a  b  c c  d d d d  e e e e e") == ["e", "d", "a"]
    assert top_three_words("e e e e DDD ddd DdD: ddd ddd aa aA Aa, bb cc cC e e e") == ["e", "ddd", "aa"]
    assert top_three_words("  //wont won't won't ") == ["won't", "wont"]
    assert top_three_words("  , e   .. ") == ["e"]
    assert top_three_words("  ...  ") == []
    assert top_three_words("  '  ") == []
    assert top_three_words("  '''  ") == []
