package sorts

// program for modifying Selection Sort
// so that it becomes stable.
fun stableSelectionSort(a: IntArray, n: Int) {
    // Iterate through array elements
    for (i in 0 until n - 1) {

        // Loop invariant : Elements till
        // a[i - 1] are already sorted.

        // Find minimum element from
        // arr[i] to arr[n - 1].
        var min = i
        for (j in i + 1 until n)
            if (a[min] > a[j])
                min = j

        // Move minimum element at current i.
        val key = a[min]
        while (min > i) {
            a[min] = a[min - 1]
            min--
        }
        a[i] = key
    }
}

fun printArray(a: IntArray, n: Int) {
    for (i in 0 until n) print(a[i].toString() + " ")
    println()
}

// Driver code
fun main() {
    val a = intArrayOf(4, 5, 3, 2, 4, 1)
    val n = a.size
    stableSelectionSort(a, n)
    printArray(a, n)
}