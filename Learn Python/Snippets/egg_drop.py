cache = {}


def egg_drop(eggs, floors):
    # no eggs -> no drops
    if eggs == 0:
        return 0

    # If there are no floors, then no trials needed. OR if there is one floor, one trial needed.
    if floors == 1 or floors == 0:
        return floors

    # We need k trials for one egg and k floors
    if eggs == 1:
        return floors

    if (eggs, floors) in cache:
        return cache[(eggs, floors)]

    minimum = float('inf')

    # Consider all possible drops from 1st floor to kth floor
    for floor in range(1, floors + 1):
        res = max(egg_drop(eggs - 1, floor - 1), egg_drop(eggs, floors - floor))
        if res < minimum:
            minimum = res

    cache[(eggs, floors)] = minimum + 1  # plus one - we drop at this floor
    return cache[(eggs, floors)]


print()


# h = c(eggs, 1) + c(eggs, 2) + ... + c(eggs, tries).
# c(n, k) = c(n, k - 1) * (n - k + 1) / k = c(n, k - 2) * (n - (k - 1) + 1) / (k - 1) * (n - k - 1) / k ... etc
def max_determinable_height(eggs, tries):
    if eggs >= tries:
        return (2 ** tries) - 1  # just do binary search

    h, t = 0, 1
    for k in range(1, eggs + 1):
        t = t * (tries - k + 1) // k
        h += t
    return h


def main():
    assert egg_drop(0, 10) == 0
    assert egg_drop(10, 0) == 0
    assert egg_drop(2, 10) == 4
    assert egg_drop(2, 100) == 14

    assert max_determinable_height(2, 14) == 105
    assert max_determinable_height(7, 20) == 137979


if __name__ == "__main__":
    main()
