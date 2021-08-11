from collections import Counter


# my solution for this kata: https://www.codewars.com/kata/5629db57620258aa9d000014/


def mix(s1: str, s2: str):
    s1_d = Counter([c for c in s1 if c.islower()])
    s2_d = Counter([c for c in s2 if c.islower()])
    s = {}
    for (k, v) in s1_d.items():
        if k not in s2_d or v > s2_d[k]:
            s[k] = (v, "1")
        elif v < s2_d[k]:
            s[k] = (s2_d[k], "2")
        elif v == s2_d[k]:
            s[k] = (v, "=")

    s.update({k: (v, "2") for (k, v) in s2_d.items() if k not in s1_d})
    s = {k: v for (k, v) in s.items() if v[0] > 1}
    result = ""
    for (k, v) in sorted(s.items(), key=lambda kv: (-kv[1][0], ord(kv[1][1]), ord(kv[0]) - ord('z'))):
        result += f"{v[1]}:{k * v[0]}/"

    return result[:-1]


if __name__ == '__main__':
    assert mix("Are they here", "yes, they are here") == "2:eeeee/2:yy/=:hh/=:rr"
    assert mix("Sadus:cpms>orqn3zecwGvnznSgacs", "MynwdKizfd$lvse+gnbaGydxyXzayp") == \
           '2:yyyy/1:ccc/1:nnn/1:sss/2:ddd/=:aa/=:zz'
    assert mix("looping is fun but dangerous", "less dangerous than coding") == \
           "1:ooo/1:uuu/2:sss/=:nnn/1:ii/2:aa/2:dd/2:ee/=:gg"
    assert mix(" In many languages", " there's a pair of functions") == \
           "1:aaa/1:nnn/1:gg/2:ee/2:ff/2:ii/2:oo/2:rr/2:ss/2:tt"
    assert mix("Lords of the Fallen", "gamekult") == "1:ee/1:ll/1:oo"
    assert mix("codewars", "codewars") == ""
    assert mix("A generation must confront the looming ",
               "codewarrs") == "1:nnnnn/1:ooooo/1:tttt/1:eee/1:gg/1:ii/1:mm/=:rr"
