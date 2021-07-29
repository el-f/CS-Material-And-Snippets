package snippets

import kotlin.test.assertEquals

/*
    solution for this kata: https://www.codewars.com/kata/5254ca2719453dcc0b00027d
    (all permutations of an input string)
 */

var solution: MutableSet<String> = HashSet()

fun singlePermutations(s: String): List<String> {
    solution.clear()
    calcPermutations(s, "")
    return ArrayList(solution)
}

fun calcPermutations(str: String, ans: String) {
    if (str.isEmpty()) {
        solution.add(ans)
        return
    }
    for (i in str.indices) {
        val ros = str.substring(0, i) + str.substring(i + 1)
        calcPermutations(ros, ans + str[i])
    }
}

fun main() {
    assertEquals(
        listOf("a"),
        singlePermutations("a").sorted()
    )

    assertEquals(
        listOf("ab", "ba"),
        singlePermutations("ab").sorted()
    )

    assertEquals(
        listOf("aabb", "abab", "abba", "baab", "baba", "bbaa"),
        singlePermutations("aabb").sorted()
    )
}
