package recursions

import kotlin.collections.ArrayList
import kotlin.math.abs

fun main() = nQueens()

fun nQueens(n: Int = 8, row: Int = 0, coordinates: MutableList<Pair<Int, Int>> = ArrayList()) {
    if (row == n) printBoard(n, coordinates) //placed all, now use the coordinates to print a board
    else {
        for (column in 0 until n) {
            coordinates.add(Pair(row, column))                  // add path in tree
            if (isValid(coordinates.map { it.second }))          // check updated columnIndexes
                nQueens(n, row + 1, coordinates)    
                     // explore path with recursion
            coordinates.removeLast()                   // in order to explore a different path
        }
    }
}

/*
 *  Can't be in the same row, inherit in the way we advance in the recursion,
 *  so we only check for same col or same diagonal by evaluating dx,dy
 *  if in same column distance dx is ofc 0.
 *  if in same diagonal then dx = dy:
 *      for example: (1,4) <-> (3,6) <-> (2,7)
 *          6-4 = 2 = 3-1 -> [(1,4),(3,6)] on same diagonal
 *          7-6 = 1 = 3-2 -> [(3,6),(2,7)] on same diagonal
 *      (basically if both coordinates are on the diagonal then it is the hypotenuse of a right-angle triangle)
 */
fun isValid(columnIndexes: List<Int>): Boolean {
    val currentRowIndex = columnIndexes.size - 1
    for (i in 0 until currentRowIndex) {
        val dx = abs(columnIndexes[i] - columnIndexes[currentRowIndex])
        val dy = currentRowIndex - i
        if (dx == 0 /*same col*/ || dx == dy /*same diag*/) return false
    }
    return true
}

fun printBoard(n: Int, coordinates: List<Pair<Int, Int>>) {
    println(coordinates)
    val matrix = Array(n) { BooleanArray(n) }
    coordinates.forEach { matrix[it.first][it.second] = true }
    matrix.indices.forEach { row ->
        matrix[row].indices.forEach { col ->
            print(if (matrix[row][col]) "  ■" else "  □")
        }
        println()
    }
    println("  ~~~~~~~~~~~~~~~~~~~~~~")
}