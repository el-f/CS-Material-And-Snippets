package recursions

fun main() {
    val array = listOf('a', 'b', 'c', 'd')
    printSubgroups(array.size, array)

    sumsPowerSets(sum = 10)
}

fun printSubgroups(j: Int, m: List<Char>) {
    if (j == 0) {
        print('{')
        m.forEach { print(if (it == m.last()) it else "$it, ") }
        println('}')
    } else {
        printSubgroups(j - 1, m)
        printSubgroups(j - 1, m - m[j - 1])
    }
}

fun sumsPowerSets(sum: Int, results: List<Int> = ArrayList()) {
    if (sum <= 0) println(results).also { return }

    for (i in 1..sum) {
        sumsPowerSets(sum - i, results + i)
    }
}