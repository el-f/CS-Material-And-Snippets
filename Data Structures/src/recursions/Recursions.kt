package recursions


fun main() {
    println(T_BS_rec(10))
}

/*
 *  T(1) = 1 <-> for arr of size 1 only 1 action needed.
 *  T(n) = T(n/2) + 1 = 2 + T(n/4) = 3 + T(n/8) = ... =
 *  = i + T(n/2^i)
 *  -> n/2^i = 1 -> i = lg(n) ->
 *  -> T(n) = lg(n) + T(1) = lg(n) +1 -> O(lg(n))
 */
fun T_BS_rec(n: Int): Int {
    return if (n <= 1) 1 else 1 + T_BS_rec(n / 2)
}

//the binary search recursive code
fun binarySearch_Rec(arr: IntArray, left: Int, right: Int, x: Int): Int {
    if (right >= left) {
        val mid = left + (right - left) / 2
        if (arr[mid] == x) return mid
        return if (arr[mid] > x) binarySearch_Rec(arr, left, mid - 1, x)
        else binarySearch_Rec(arr, mid + 1, right, x)
    }
    return -1 //not present
}

//non recursive binary search
fun binarySearch(arr: IntArray, x: Int): Int {
    var left = 0
    var right = arr.size - 1
    while (left <= right) {
        val mid = left + (right - left) / 2
        // Check if x is present at mid
        if (arr[mid] == x) return mid
        // If x greater, ignore left half
        if (arr[mid] < x) left = mid + 1 else right = mid - 1
    }
    return -1 // not present
}

/*
    count actions in find_min_rec
    T(n) = 2^i * T(n/2^i) + (2^i - 1)
    goes until n/2^i = 1
    -> i = lg(n)
    -> T(n) = n * T(1) + n-1 = 2n-1 -> O(n)
 */
fun T_findMin_rec(n: Int): Int {
    return if (n <= 1) 1 else 2 * T_findMin_rec(n / 2) + 1
}

// non recursive code
fun findMin(A: IntArray): Int {
    // returns the smallest number in an array with n numbers
    var min = A[0]
    for (i in 1 until A.size) if (A[i] < min) min = A[i]
    return min
}