
from math import sqrt

# dynamic programming solution for the perfect squares sum problem
def pss_dp(n):
    dp = [n] * (n + 1)

    for i in range(n):
        if i * i <= n:
            dp[i * i] = 1

    for i in range(1, n + 1):
        for j in range(sqrt(i)):
            dp[i] = min(dp[i], dp[i - j * j] + 1)

    return dp[n]

 
# Mathematical solution for the perfect squares sum problem
# The solution is based on Lagrange’s Four Square Theorem.
# According to the theorem, there can be atmost 4 solutions to the problem,
# i.e. 1, 2, 3, 4
 
# returns True if the input number x is a square number,
# else returns False
def is_square(x):
    sqRoot = int(sqrt(x));
    return (sqRoot * sqRoot == x);
 
# Function to count minimum squares that sum to n
def pfss_math(n):
   
    # ans = 1 if the number is a perfect square
    if is_square(n):
        return 1;
     
    # ans = 2:
    # we check for each i if n - (i * i) is a perfect
    # square
    for i in range(1, int(sqrt(n))):
        if is_square(n - (i * i)):
            return 2;
         
    # ans = 4
    # possible if the number is representable in the form
    # 4^a (8*b + 7).
    while n % 4 == 0:
        n >>= 2;
     
    if n % 8 == 7:
        return 4;
     
    # since all the other cases have been evaluated, the
    # answer can only then be 3 if the program reaches here
    return 3;