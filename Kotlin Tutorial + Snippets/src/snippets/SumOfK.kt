package snippets

import kotlin.collections.ArrayList
import kotlin.test.assertEquals

// solution for this kata: 55e7280b40e1c4a06d0000aa
// (best possible sum of <k> elements under constraint <t>)

private var sum = 0
private var T = 0
private var K = 0

private fun calculateSum(superSet: List<Int>, idx: Int, current: MutableList<Int>) {
    if (current.size == K) {
        val res = current.sum()
        if (res in (sum + 1)..T) sum = res
        return
    }
    if (idx == superSet.size) return

    val x = superSet[idx]
    current.add(x)
    calculateSum(superSet, idx + 1, current)
    current.remove(x)
    calculateSum(superSet, idx + 1, current)
}

fun chooseBestSum(t: Int, k: Int, ls: List<Int>): Int {
    T = t; K = k; sum = -1
    calculateSum(ls, 0, ArrayList())
    return sum
}


fun main() {
    assertEquals(163, chooseBestSum(163, 3, listOf(50, 55, 56, 57, 58)))
    assertEquals(-1, chooseBestSum(163, 3, listOf(50)))
}