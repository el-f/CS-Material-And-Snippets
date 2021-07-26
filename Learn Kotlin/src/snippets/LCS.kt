package snippets

import kotlin.collections.HashMap

val cache: MutableMap<Pair<String, String>, String> = HashMap()

fun lcs(a: String, b: String): String {
    if (a.isEmpty() || b.isEmpty()) return ""

    val current = Pair(a, b)
    if (cache.containsKey(current)) return cache[current].orEmpty()

    val result = if (a.last() == b.last()) {
        lcs(a.dropLast(1), b.dropLast(1)) + a.last()
    } else {
        val s1 = lcs(a.dropLast(1), b)
        val s2 = lcs(a, b.dropLast(1))
        if (s1.length > s2.length) s1 else s2
    }

    cache[current] = result
    return result
}

// ************************************************************************************
// pretty much same solution but going forwards instead of backwards through the string
val m = mutableMapOf<Pair<String, String>, String>()

fun lcs2(a: String, b: String): String {
    if (a.isEmpty() || b.isEmpty()) return ""
    if (a.first() == b.first()) return a.first() + lcs2(a.drop(1), b.drop(1))

    val s1 = m.getOrPut(a to b.drop(1)) { lcs2(a, b.drop(1)) }
    val s2 = m.getOrPut(a.drop(1) to b) { lcs2(a.drop(1), b) }
    return if (s1.length > s2.length) s1 else s2
}
// ************************************************************************************

fun main() {
    //test cases
    arrayOf(
        (""           == lcs("", "")),
        ("final"      == lcs("nothardlythefinaltest", "zzzfinallyzzz")),
        ("abc"        == lcs("abcdef", "abc")),
        ("acf"        == lcs("abcdef", "acf")),
        ("nottest"    == lcs("anothertest", "notatest")),
        ("12356"      == lcs("132535365", "123456789")),

        (""           == lcs2("", "")),
        ("final"      == lcs2("nothardlythefinaltest", "zzzfinallyzzz")),
        ("abc"        == lcs2("abcdef", "abc")),
        ("acf"        == lcs2("abcdef", "acf")),
        ("nottest"    == lcs2("anothertest", "notatest")),
        ("12356"      == lcs2("132535365", "123456789")),
    ).forEach(::assert)
}