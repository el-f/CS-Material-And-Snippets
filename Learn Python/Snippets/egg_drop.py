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

    cache[(eggs, floors)] = minimum + 1 # plus one - we drop at this floor
    return cache[(eggs, floors)]


if __name__ == "__main__":
    assert egg_drop(0, 10) == 0
    assert egg_drop(10, 0) == 0
    assert egg_drop(2, 10) == 4
    assert egg_drop(2, 100) == 14
