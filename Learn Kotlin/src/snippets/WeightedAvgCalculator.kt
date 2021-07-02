package snippets

import java.io.File
import kotlin.math.max

fun main() {
    println("------------ All Marks ------------------")
    var wac = WeightedAvgCalculator("Learn Kotlin/src/snippets/myMarks")
    wac.printAll()
    wac.printAverage()
    wac.printAllRanges()


    println("\n-------- technology Marks ---------------")
    wac = WeightedAvgCalculator("Learn Kotlin/src/snippets/myTechnologyMarks")
    wac.printAll()
    wac.printAverage()
    wac.printAllRanges()
}

class WeightedAvgCalculator(
        filePath: String?,
        private var marks: MutableList<Triple<String, Int, Double>> = ArrayList(),
        private var allNaz: Double = 0.0,
) {
    private val firstPrintLineLen: Int = 25
    private val secondPrintLineLen: Int = 9

    init {
        if (filePath != null)
            initListFromFile(filePath)
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

    fun printAverage() = println("\nAverage - ${"%.3f".format(getAvg())}\n")

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
        println("Course                     %           NZ")
        println("-----------------------------------------")
        marks.forEach {
            print(it.first + " ")
            print("-".repeat(max(firstPrintLineLen, it.first.length + 1) - it.first.length))
            print(" " + it.second + " ")
            print("-".repeat(secondPrintLineLen - it.second.toString().length))
            println(" " + it.third)
        }
    }
}
