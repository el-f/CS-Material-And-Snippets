package snippets

import java.nio.file.Files
import java.nio.file.Path

fun main() {
    val wac = WeightedAvgCalculator("Learn Kotlin/src/snippets/myMarks")
    wac.printAll()
    wac.printAverage()
    wac.printRange(70,80)
    wac.printRange(80,90)
    wac.printRange(90,100)
    wac.printRange(100,101)
}

class WeightedAvgCalculator(
    filePath: String?,
    private var list: MutableList<Triple<String, Int, Double>> = ArrayList(),
    private var allNaz: Double = 0.0,
) {
    init {
        if (filePath != null)
            initListFromFile(filePath)
    }

    private fun initListFromFile(filePath: String) {
        Files.lines(Path.of(filePath))
            .filter { it.isNotEmpty() }
            .map { it.split(Regex("[\\s]+")) }
            .forEach { list.add(Triple(it[0], it[1].toInt(), it[2].toDouble())) }
        allNaz = list.map { it.third }.sum()
    }

    private fun getAvg() = list.map { it.second * it.third / allNaz }.sum()

    fun printAverage() = println("\nAverage - ${"%.3f".format(getAvg())}\n")

    fun printRange(low: Int, high: Int) {
        println(
            "${list.filter { it.second in low until high }.size}" +
                " Marks at Range of ($low-${high - 1}) Out of ${list.size} Marks"
        )
    }

    fun printAll() = list.forEach {
        println("${it.first} - ${it.second} (${it.third} nz)")
    }
}
