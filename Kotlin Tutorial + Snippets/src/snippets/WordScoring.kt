package snippets

//  57eb8fcdf670e99d9b000272

fun score(word: String) = word.sumOf { it.code - 'a'.code + 1 }
fun high(words: String) = words.split(' ').maxByOrNull(::score)


fun main() {
    println(high("b aa"))
    println(high("aa b"))
    println(high("The quick brown fox jumps over the lazy dog"))
}