import math


# 5993e6f701726f0998000030

def insane_inc_or_dec(n):
    return (math.comb(n + 10, 10) + math.comb(n + 9, 9) - 10 * n) % 12345787 - 2
