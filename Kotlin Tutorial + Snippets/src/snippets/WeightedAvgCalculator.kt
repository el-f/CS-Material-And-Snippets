package snippets

import Snippets.TableList
import java.io.File
import kotlin.math.roundToInt

fun main() {
    println("All Marks:")
    var wac = WeightedAvgCalculator("Kotlin Tutorial + Snippets/src/snippets/myMarks")
    wac.printAll().also { println() }
    wac.printAverage()
    wac.printRoundedAverage().also { println() }
    wac.printAllRanges().also { println() }


    println("\nTechnology Marks:")
    wac = WeightedAvgCalculator("Kotlin Tutorial + Snippets/src/snippets/myTechnologyMarks")
    wac.printAll().also { println() }
    wac.printAverage()
    wac.printRoundedAverage().also { println() }
    wac.printAllRanges()
}

class WeightedAvgCalculator(
    filePath: String?,
    private var marks: MutableList<Triple<String, Int, Double>> = ArrayList(),
    private var allNaz: Double = 0.0,
) {

    init {
        if (filePath != null) initListFromFile(filePath)
    }

    private fun initListFromFile(filePath: String) {
        File(filePath)
            .readLines()
            .filter { it.isNotEmpty() && !it.startsWith("#") }
            .map { it.split(Regex(",")) }
            .forEach { marks.add(Triple(it[0].trim(), it[1].trim().toInt(), it[2].trim().toDouble())) }
        allNaz = marks.sumOf { it.third }
    }

    private fun getAvg() = marks.sumOf { it.second * it.third / allNaz }

    fun printAverage() = println("Average - ${"%.3f".format(getAvg())}")

    fun printRoundedAverage() = println("Rounded Average - ${getAvg().roundToInt()}")

    private fun printRange(low: Int, high: Int) {
        println(
            "${marks.filter { it.second in low..high }.size}" +
                    " Marks at Range of ($low-$high) Out of ${marks.size} Marks"
        )
    }

    fun printAllRanges() {
        for (i in 0..90 step 10) {
            if (marks.any { it.second in i..i + 9 }) {
                printRange(i, i + 9)
            }
        }
        printRange(100, 100)
    }

    fun printAll() {
        val tl = TableList("#", "Course", "%", "NZ").withUnicode(true)
        marks.forEachIndexed { idx, t -> tl.addRow(idx + 1, t.first, t.second, t.third) }
        tl.print()
    }
}
