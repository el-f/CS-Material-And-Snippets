package recursions

fun main() {
    val array = listOf('a', 'b', 'c', 'd')
    printSubgroups(array.size, array)
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