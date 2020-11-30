package snippets

fun main() {
    println(fact(4))
    println(tail_fact(4))
}

//regular recursion - inefficient
fun fact(n: Int): Int {
    return if (n == 1) 1 else n * fact(n - 1)
}

//tail recursion - more efficient
fun tail_fact(n: Int, m: Int = 1): Int {
    return if (n == 1) m else tail_fact(n - 1, n * m)
}