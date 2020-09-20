package assignments._IV

import assignments._IV.InputOrder.*
import kotlin.random.Random

enum class InputOrder { Randomized, Sorted, Reversed }

fun main() {
    println("Sorted Input Runtimes: ")
    run(Sorted)

    println("\nRandom Input Runtimes: ")
    for (i in 1..3) run(Randomized)

    println("\nReversed Input Runtimes: ")
    run(Reversed)
}

fun run(order: InputOrder, from: Int = 1000, to: Int = 1000000, step: Int = 10) {
    var i = from
    while (i <= to) {
        analyze(i, order)
        i *= step
    }
}

fun analyze(size: Int, order: InputOrder) {
    val arr = IntArray(size)
    for (i in 0 until size)
        arr[i] = Random.nextInt(0, size * 10)

    when (order) {
        Sorted -> arr.sort()
        Reversed -> arr.reverse()
        Randomized -> {
        }
    }
    println(" ${measureTime { insertionSort(arr) }} milliseconds for $order array of size $size")
}

fun insertionSort(arr: IntArray) {
    for (i in 1 until arr.size) {
        val curr = arr[i]
        var j = i - 1
        while (j >= 0 && arr[j] > curr) {
            arr[j + 1] = arr[j--]
        }
        arr[j + 1] = curr
        if (i % (arr.size / 20) == 0) print("■") //progress bar
    }
}

inline fun measureTime(executable: () -> Unit): Long {
    val start = System.currentTimeMillis()
    executable()
    return System.currentTimeMillis() - start
}