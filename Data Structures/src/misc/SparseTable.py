# Python3 program to do range minimum query using sparse table ( Credit to GFG )
import numpy


# Fills lookup array lookup[][] in
# bottom up manner.
def build_sparse_table(arr):
    size = len(arr)

    # Initialize M for the intervals
    # with length 1
    for i in range(0, size):
        lookup[i][0] = arr[i]

    j = 1

    # Compute values from smaller to
    # bigger intervals
    while (1 << j) <= size:

        # Compute minimum value for all
        # intervals with size 2^j
        i = 0
        while (i + (1 << j) - 1) < size:

            # For arr[2][10], we compare arr[lookup[0][7]]
            # and arr[lookup[3][10]]
            if lookup[i][j - 1] < lookup[i + (1 << (j - 1))][j - 1]:
                lookup[i][j] = lookup[i][j - 1]
            else:
                lookup[i][j] = lookup[i + (1 << (j - 1))][j - 1]

            i += 1
        j += 1


# Returns minimum of arr[left..right]
def query(left, right):
    # Find highest power of 2 that is smaller
    # than or equal to count of elements in
    # given range. For [2, 10], j = 3
    j = int(numpy.log2(right - left + 1))

    # Compute minimum of last 2^j elements
    # with first 2^j elements in range.
    # For [2, 10], we compare arr[lookup[0][3]]
    # and arr[lookup[3][3]],
    if lookup[left][j] <= lookup[right - (1 << j) + 1][j]:
        return lookup[left][j]

    return lookup[right - (1 << j) + 1][j]


if __name__ == "__main__":

    a = [7, 2, 3, 0, 5, 10, 3, 12, 18]
    MAX = 500

    # lookup[i][j] is going to store minimum
    # value in arr[i..j]. Ideally lookup table
    # size should not be fixed and should be
    # determined using n Log n. It is kept
    # constant to keep code simple.
    lookup = [[0 for i in range(MAX)] for j in range(MAX)]

    build_sparse_table(a)
    print(query(0, 4))
    print(query(4, 7))
    print(query(7, 8))
