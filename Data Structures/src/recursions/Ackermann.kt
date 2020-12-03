package snippets


fun main() {
    for (m in 0..3)
        for (n in 0..4)
            println("for (" + m + "," + n + ") - " + acker(m, n))
}

fun acker(m: Int, n: Int): Int {
    if (m == 0) return n + 1
    return if (n == 0) acker(m - 1, 1) else acker(m - 1, acker(m, n - 1))
}