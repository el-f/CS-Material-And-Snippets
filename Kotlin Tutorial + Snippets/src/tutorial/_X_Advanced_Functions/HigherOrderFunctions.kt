package tutorial._X_Advanced_Functions


fun <T> printFilteredStrings(list: List<T>, predicate: (T) -> Boolean) {
    list.forEach {
        if (predicate(it))
            println(it)
    }
    println("~~~")
}

//nullable function
fun printFilteredStrings2(list: List<String>, predicate: ((String) -> Boolean)?) {
    list.forEach {
        if (predicate?.invoke(it) == true)
            println(it)
    }
    println("><><>")
}

val predicate: (String) -> Boolean = { it.startsWith("J") }

fun getPrintPredicate(): (String) -> Boolean {
    return { it.startsWith("J") }
}

fun main() {
    val list = listOf("Kotlin", "Java", "JavaScript", "Python", "C++")
    printFilteredStrings(list) {
        it.startsWith("J")
    }
    printFilteredStrings(list, predicate)
    printFilteredStrings(list, getPrintPredicate())
    printFilteredStrings2(list, null)

}