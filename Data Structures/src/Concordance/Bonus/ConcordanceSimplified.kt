package Concordance.Bonus

import Concordance.BIBLE_KING_JAMES_EDITION
import Concordance.Bonus.ConcordanceSimplified.*
import java.io.File
import java.nio.file.Files
import java.util.*
import kotlin.collections.HashMap
import kotlin.streams.toList

/**
 * I took the core functionality of the project and instead of implementing it with my own custom
 * TreeMap/HashMap + LinkedList as required, I used the language's own implementations.
 * Surprisingly, I didn't notice much of a performance improvement.
 */
class ConcordanceSimplified(file: File, structure: Structure) {
    enum class Structure {
        TREE_MAP, HASH_MAP
    }

    private val map: MutableMap<String, LinkedList<Int>>
    fun search(word: String): LinkedList<Int>? {
        return map[word.lowercase()]
    }

    val words: Collection<String>
        get() = if (map is TreeMap) map.keys else map.keys.sorted()

    private fun checkForOneLetterWords(word: String): Boolean {
        return word.length != 1 || "ai".contains(word)
    }

    init {
        val lines = Files.lines(file.toPath()).toList()

        map = when (structure) {
            Structure.TREE_MAP -> TreeMap()
            Structure.HASH_MAP -> HashMap()
        }
        for (i in lines.indices) {
            if (lines[i].isNotEmpty())
                for (word in lines[i]
                    .replace("-".toRegex(), " ")
                    .replace("[^\\p{Alpha}\\s]".toRegex(), "")
                    .trim { it <= ' ' }
                    .lowercase()
                    .split("[\\s]+".toRegex())
                    .toTypedArray()
                ) {
                    if (word.isNotEmpty() && checkForOneLetterWords(word)) {
                        map.putIfAbsent(word, LinkedList())
                        map[word]!!.add(i + 1)
                    }
                }
        }
    }
}

//-------------------------------------------------------------------------------------------//

fun main() {
    var start = System.currentTimeMillis()
    val concordance = ConcordanceSimplified(File(BIBLE_KING_JAMES_EDITION), Structure.TREE_MAP)
    println("Concordance Created In: " + (System.currentTimeMillis() - start) + "ms")
    start = System.currentTimeMillis()

    println(concordance.search("moses"))
    println("Search Finished In: " + (System.currentTimeMillis() - start) + "ms")

    start = System.currentTimeMillis()
    println(concordance.words)
    println("Word set generated in: " + (System.currentTimeMillis() - start) + "ms")
}