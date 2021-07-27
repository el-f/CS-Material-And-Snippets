package snippets

import kotlin.collections.HashMap
import kotlin.test.assertTrue

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

fun doTests(lcsFunction: (String, String) -> String) {
    arrayOf(
            (""           == lcsFunction("", "")),
            ("final"      == lcsFunction("nothardlythefinaltest", "zzzfinallyzzz")),
            ("abc"        == lcsFunction("abcdef", "abc")),
            ("acf"        == lcsFunction("abcdef", "acf")),
            ("nottest"    == lcsFunction("anothertest", "notatest")),
            ("12356"      == lcsFunction("132535365", "123456789")),
    ).forEach(::assertTrue)
    cache.clear()
}

fun main() {
    doTests(::lcs)
    doTests(::lcs2)
}