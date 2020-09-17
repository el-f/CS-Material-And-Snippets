package recursions

fun main() {
    val arr = arrayOf(1, 5, 6, 8, 9, 2)
    print(findMinMax(arr))
}

fun findMax(arr: Array<Int>, size: Int = arr.size, max: Int = Int.MIN_VALUE): Int {
    if (size == 0) return max
    return findMax(arr, size - 1, maxOf(arr[size - 1], max))
}

fun findMinMax(arr: Array<Int>, size: Int = arr.size,
               minMax: Pair<Int /*min*/, Int /*max*/> = Pair(
                       Int.MAX_VALUE,
                       Int.MIN_VALUE)): Pair<Int, Int> {
    if (size == 0) return minMax
    return findMinMax(arr, size - 1, Pair(minOf(arr[size - 1], minMax.first),
            maxOf(arr[size - 1], minMax.second)))
}

