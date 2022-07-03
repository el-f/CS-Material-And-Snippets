# 61a2fcac3411ca0027e71108

#    [0, 2, 3, 7, 10, 12]
#       [1, 5, 7, 8]
# 
# 0->2->3->7->10->12 => 34
# 0->2->3->7->8      => 20
# 1->5->7->8         => 21
# 1->5->7->10->12    => 35 (maximum path)


def mps(l1, l2, a=0, b=0):
    while l1 and l2:
        if l1[-1] > l2[-1]:
            a += l1.pop()
        elif l1[-1] < l2[-1]:
            b += l2.pop()
        else:
            a = b = max(a+l1.pop(), b+l2.pop())
    return max(a+sum(l1), b+sum(l2))


def mps_v2(a, b):
    i, j, A, B = 0, 0, 0, 0
    while i < len(a) and j < len(b):
        x, y = a[i], b[j]
        if x == y:
            A = B = max(A, B)
        if x <= y:
            i, A = i+1, A+x
        if x >= y:
            j, B = j+1, B+y
    return max(A+sum(a[i:]), B+sum(b[j:]))


def mps_v3(l1, l2):

    # Get common numbers of the lists 'l1' & 'l2'
    common = list(set(set(l1).intersection(l2)))
    common.sort()

    # When there is no common element, return sum of the bigger list
    if (len(common) < 1):
        return(max([sum(l1), sum(l2)]))

    # Loop over each common element & slice the vectors at it
    max_sum = 0
    for curr_common in common:

        # Add the maximum of the sums over l1 & l2 up to 'curr_common'
        max_sum = max_sum + max([sum(l1[:l1.index(curr_common) + 1]),
                                 sum(l2[:l2.index(curr_common) + 1])])

        # Remove all elements from l1 & l2 up to 'curr_common'
        # (the max. sum was already added to 'max_sum')
        del l1[:l1.index(curr_common) + 1]
        del l2[:l2.index(curr_common) + 1]

    # Last step, add maximum sum of the remaining l1 & l2
    max_sum = max_sum + max([sum(l1), sum(l2)])

    return(max_sum)
