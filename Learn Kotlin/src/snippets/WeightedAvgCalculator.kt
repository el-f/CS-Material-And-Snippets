package snippets

import java.nio.file.Files
import java.nio.file.Path

fun main() {
    println("------ All Marks ------")
    var wac = WeightedAvgCalculator("Learn Kotlin/src/snippets/myMarks")
    wac.printAll()
    wac.printAverage()
    wac.printRange(70, 79)
    wac.printRange(80, 89)
    wac.printRange(90, 99)
    wac.printRange(100, 100)

    println("\n------ technology Marks ------")
    wac = WeightedAvgCalculator("Learn Kotlin/src/snippets/myTechnologyMarks")
    wac.printAll()
    wac.printAverage()
    wac.printRange(70, 79)
    wac.printRange(80, 89)
    wac.printRange(90, 99)
    wac.printRange(100, 100)
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
            .map { it.split(Regex(",")) }
            .forEach { list.add(Triple(it[0].trim(), it[1].trim().toInt(), it[2].trim().toDouble())) }
        allNaz = list.map { it.third }.sum()
    }

    private fun getAvg() = list.map { it.second * it.third / allNaz }.sum()

    fun printAverage() = println("\nAverage - ${"%.3f".format(getAvg())}\n")

    fun printRange(low: Int, high: Int) {
        println(
            "${list.filter { it.second in low..high }.size}" +
                    " Marks at Range of ($low-$high) Out of ${list.size} Marks"
        )
    }

    fun printAll() = list.forEach {
        println("${it.first} - ${it.second} (${it.third} nz)")
    }
}
