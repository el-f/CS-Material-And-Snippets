package snippets

import java.util.*
import kotlin.math.sqrt

fun main() {
    val sudokuBoard = Sudoku(Scanner(System.`in`))
    if (!sudokuBoard.checkSudoku()) {
        println("Not a valid Sudoku!")
    } else println("A valid Sudoku!")
    println("\n~~End of the Sudoku program~~\n-------")
}

class Sudoku(s: Scanner) {
    private val mat: Array<IntArray>
    private val totalSize: Int
    private val root: Int

    private fun init(s: Scanner) {
        var temp: Int
        var initializedCell: Boolean
        for (i in mat.indices) {
            println("Filling Row Number ${i + 1}")
            for (j in mat[i].indices) do {
                initializedCell = false
                println("Please enter a number between 1-${mat.size} for cell [${i + 1}, ${j + 1}]")
                temp = s.nextInt()
                if (temp in 1..totalSize) {
                    mat[i][j] = temp
                    initializedCell = true
                }
            } while (!initializedCell)
        }
    }

    private fun show() {
        for (i in 0 until totalSize) {
            for (element in mat[i]) System.out.printf("%5d", element)
            println()
        }
    }

    fun checkSudoku(): Boolean {
        for (i in 0 until totalSize) {
            if (!isValid(i)) return false
        }
        for (sRowIndex in 0 until root) {
            for (sColIndex in 0 until root) {
                if (!isValidSudokuQuadrant(sRowIndex, sColIndex)) return false
            }
        }
        return true
    }

    private fun checkIndexValidity(index: Int): Boolean {
        if (index < 0 || index > totalSize) {
            println("Bad Index")
            return false
        }
        return true
    }

    private fun checkNum(num: Boolean, index: Int) = !checkIndexValidity(index) || num

    private fun isValid(index: Int): Boolean {
        if (!checkIndexValidity(index)) return false
        val rowSeenNumbersTracker = BooleanArray(totalSize + 1)
        val colSeenNumbersTracker = BooleanArray(totalSize + 1)
        for (i in 0 until totalSize) {
            if (checkNum(rowSeenNumbersTracker[mat[index][i]], mat[index][i])) {
                return false
            } else rowSeenNumbersTracker[mat[index][i]] = true
            if (checkNum(colSeenNumbersTracker[mat[i][index]], mat[i][index])) {
                return false
            } else colSeenNumbersTracker[mat[i][index]] = true
        }
        return true
    }

    private fun isValidSudokuQuadrant(sR: Int, sC: Int): Boolean {
        if (sR < 0 || sC < 0 || sR > root || sC > root) {
            println("bad index")
            return false
        }
        val seenNumbersTracker = BooleanArray(totalSize + 1)
        val rowIndex = sR * root
        val colIndex = sC * root
        for (r in rowIndex until rowIndex + root) {
            for (c in colIndex until colIndex + root) {
                // here i don't check that numbers are in range since all numbers were already
                // checked in row/column checks.
                if (seenNumbersTracker[mat[r][c]]) {
                    return false
                } else seenNumbersTracker[mat[r][c]] = true
            }
        }
        return true
    }

    init {
        var temp: Int
        do {
            println(
                "Please enter a natural number N which has an natural square root for the total size NxN of the board"
            )
            temp = s.nextInt()
        } while (sqrt(temp.toDouble()) != sqrt(temp.toDouble()) || temp < 1)
        totalSize = temp
        root = sqrt(totalSize.toDouble()).toInt()
        mat = Array(totalSize) { IntArray(totalSize) }
        init(s)
        show()
    }
}