def longest_palindrome(s):
    longest = 0
    for i in range(len(s)):
        for j in range(i + 1, len(s) + 1):
            if s[i:j] == s[i:j][::-1]:
                if j - i > longest:
                    longest = j - i
    return longest
