package sorts

import java.util.*

fun main() {
    var arr = intArrayOf(112, 1, 22, 55, 10, 5, 0)
    insertionSort(arr)
    for (i in arr) print("$i ")
    /*---runtime testing---*/
    var i = 25000
    while (i <= 1000000) {
        val r = Random()
        arr = IntArray(i)
        for (j in 0 until i) arr[j] = r.nextInt()
        val start = System.currentTimeMillis()
        insertionSort(arr)
        val time = System.currentTimeMillis() - start
        System.out.printf(
            "Insertion sort of %,d elements took %.3f seconds%n",
            i, time / 1e3
        )
        i *= 2
    }
}

fun insertionSort(arr: IntArray) {
    val n = arr.size
    for (i in 1 until n) {
        val key = arr[i]
        var j = i - 1

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j]
            j -= 1
        }
        arr[j + 1] = key
    }
}
