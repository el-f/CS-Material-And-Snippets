package _legacy_copies

import java.util.*

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
        var initilizedCell: Boolean
        for (i in mat.indices) {
            println(
                """
                    
                    Filling Row Number ${i + 1}
                    """.trimIndent()
            )
            for (j in mat[i].indices) do {
                initilizedCell = false
                println(
                    "Please enter a number between 1-" + mat.size + " for cell [" + (i + 1)
                            + "," + (j + 1) + "]"
                )
                temp = s.nextInt()
                if (temp in 1..totalSize) {
                    mat[i][j] = temp
                    initilizedCell = true
                }
            } while (!initilizedCell)
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
            if (!isValidSudokuRow(i) || !isValidSudokuCol(i)) return false
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

    private fun isValidSudokuRow(indexRow: Int): Boolean {
        if (!checkIndexValidity(indexRow)) return false
        val numberHasBeenSeenAlready = BooleanArray(totalSize + 1)
        for (i in 0 until totalSize) {
            if (numberHasBeenSeenAlready[mat[indexRow][i]] || !checkIndexValidity(
                    mat[indexRow][i]
                )
            ) {
                return false
            } else numberHasBeenSeenAlready[mat[indexRow][i]] = true
        }
        return true
    }

    private fun isValidSudokuCol(indexCol: Int): Boolean {
        if (!checkIndexValidity(indexCol)) return false
        val numberHasBeenSeenAlready = BooleanArray(totalSize + 1)
        for (i in 0 until totalSize) {
            if (numberHasBeenSeenAlready[mat[i][indexCol]] || !checkIndexValidity(
                    mat[i][indexCol]
                )
            ) {
                return false
            } else numberHasBeenSeenAlready[mat[i][indexCol]] = true
        }
        return true
    }

    private fun isValidSudokuQuadrant(sR: Int, sC: Int): Boolean {
        if (sR < 0 || sC < 0 || sR > root || sC > root) {
            println("bad index")
            return false
        }
        val numberHasBeenSeenAlready = BooleanArray(totalSize + 1)
        val rowIndex = sR * root
        val colIndex = sC * root
        for (r in rowIndex until rowIndex + root) {
            for (c in colIndex until colIndex + root) {
                // here i don't check that numbers are in range since all numbers were already
                // checked in row/column checks.
                if (numberHasBeenSeenAlready[mat[r][c]]) {
                    return false
                } else numberHasBeenSeenAlready[mat[r][c]] = true
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
        } while (Math.sqrt(temp.toDouble()) != Math.sqrt(temp.toDouble()) || temp < 1)
        totalSize = temp
        root = Math.sqrt(totalSize.toDouble()).toInt()
        mat = Array(totalSize) { IntArray(totalSize) }
        init(s)
        show()
    }
}