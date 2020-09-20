package assignments._IV

fun main() {
    val arr = intArrayOf(16, 9, 11, 5, 10, 2, 6, 8, 1, 4, 3)
    mergeSortBottomUp(arr)
    println(arr.contentToString())
}

fun mergeSortBottomUp(arr: IntArray) {
    var width = 1
    while (width <= arr.size - 1) {
        var left = 0
        while (left < arr.size - 1) {
            merge(
                arr,
                left,
                /*mid*/ minOf(left + width - 1, arr.size - 1),
                /*right*/ minOf(left + 2 * width - 1, arr.size - 1)
            )
            left += 2 * width
        }
        width *= 2
    }
}

fun merge(arr: IntArray, left: Int, mid: Int, right: Int) {
    val leftSize = mid - left + 1
    val rightSize = right - mid
    val lArr = IntArray(leftSize)
    val rArr = IntArray(rightSize)

    var l = 0
    while (l < leftSize) lArr[l] = arr[left + l++]
    var r = 0
    while (r < rightSize) rArr[r] = arr[mid + 1 + r++]

    var i = left; r = 0; l = 0
    while (l < leftSize && r < rightSize) {
        if (lArr[l] <= rArr[r]) {
            arr[i++] = lArr[l++]
        } else {
            arr[i++] = rArr[r++]
        }
    }
    while (l < leftSize) arr[i++] = lArr[l++]
    while (r < rightSize) arr[i++] = rArr[r++]

}