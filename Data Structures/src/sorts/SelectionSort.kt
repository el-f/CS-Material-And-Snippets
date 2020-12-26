package sorts

fun selectSort(arr: IntArray) {
    val n = arr.size

    // One by one move boundary of unsorted subarray
    for (i in 0 until n - 1) {
        // Find the minimum element in unsorted array
        var minIdx = i
        for (j in i + 1 until n)
            if (arr[j] < arr[minIdx])
                minIdx = j

        // Swap the found minimum element with the first
        // element
        val temp = arr[minIdx]
        arr[minIdx] = arr[i]
        arr[i] = temp
    }
}

// Prints the array
fun printArray(arr: IntArray) {
    for (j in arr) print("$j ")
    println()
}

// Driver code to test above
fun main() {
    val arr = intArrayOf(64, 25, 12, 22, 11)
    selectSort(arr)
    println("Sorted array")
    printArray(arr)
}