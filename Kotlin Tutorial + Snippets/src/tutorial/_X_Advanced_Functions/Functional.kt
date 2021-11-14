package tutorial._X_Advanced_Functions

fun main() {
    val list = listOf("Kotlin", "Java", "JavaScript", "Python", "C++", null, null)
    list.slice(2..4)
        .forEach { println(it) }
    println()

    list
        .filterNotNull()
        .filter { it.startsWith("J") }
        .map { "num of chars in $it is ${it.length}" }
        .forEach { println(it) }
    println()

    list
        .take(4)
        .takeLast(2)
        .forEach { println(it) }
    println()
    list
        .filterNotNull()
        .associateWith { it.length }
        .forEach {
            println("${it.key} - ${it.value}")
        }
    println()

    val map = list
        .filterNotNull()
        .associateWith { it.length }

    map.forEach { (k, v) -> println("$k - $v") }
    println()

    println("${list.first()} > ${list.filterNotNull().last()}\n")
    println("${list.filterNotNull().find { it.startsWith("J") }}\n")
    println(list.filterNotNull().findLast { it.startsWith("foo") }.orEmpty())
}