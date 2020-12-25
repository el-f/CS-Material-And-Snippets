package recursions


/*
    replace every pair from right to left
 */

fun main() {
    println(replaceWithLeft(123)) // 132
    println(replaceWithLeft(1234)) // 2143
    println(replaceWithLeft(12345)) // 13254
}

fun replaceWithLeft(n: Int): Int {
    return if (n / 10 == 0) n
    else (n % 10) * 10 + ((n / 10) % 10) + replaceWithLeft(n / 100) * 100
}