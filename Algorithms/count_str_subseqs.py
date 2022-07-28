def count_subsequences(needle, haystack):
    n, m = len(needle), len(haystack)
    dp = [0] * n
    for i in range(m):
        for j in range(n - 1, -1, -1):
            if haystack[i] == needle[j]:
                dp[j] += 1 if j == 0 else dp[j - 1]
    return dp[-1]