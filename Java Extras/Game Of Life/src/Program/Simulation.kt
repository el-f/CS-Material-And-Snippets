package Program

class Simulation(var board: Array<IntArray>) {
    @JvmField
    var width: Int = board.size

    @JvmField
    var height: Int = board[0].size

    fun setAlive(x: Int, y: Int) {
        if (x < 0 || x >= width || y < 0 || y >= height) return
        board[x][y] = 1
    }

    fun setDead(x: Int, y: Int) {
        if (x < 0 || x >= width || y < 0 || y >= height) return
        board[x][y] = 0
    }

    private fun countAliveNeighbours(x: Int, y: Int): Int {
        var count = 0
        count += getCellValue(x - 1, y - 1)
        count += getCellValue(x, y - 1)
        count += getCellValue(x + 1, y - 1)
        count += getCellValue(x + 1, y)
        count += getCellValue(x - 1, y)
        count += getCellValue(x - 1, y + 1)
        count += getCellValue(x, y + 1)
        count += getCellValue(x + 1, y + 1)
        return count
    }

    fun getCellValue(x: Int, y: Int): Int {
        if (x < 0 || x >= width) return 0
        return if (y < 0 || y >= height) 0 else board[x][y]
    }

    fun step() {
        val newBoard = Array(width) { IntArray(height) }
        for (y in 0 until height) {
            for (x in 0 until width) {
                val aliveNeighbours = countAliveNeighbours(x, y)
                if (getCellValue(x, y) == 1) {
                    if (aliveNeighbours < 2) {
                        newBoard[x][y] = 0
                    } else if (aliveNeighbours == 2 || aliveNeighbours == 3) {
                        newBoard[x][y] = 1
                    } else {
                        newBoard[x][y] = 0
                    }
                } else if (aliveNeighbours == 3) {
                    newBoard[x][y] = 1
                }
            }
        }
        board = newBoard
    }

    fun toggleState(x: Int, y: Int) {
        if (getCellValue(x, y) == 0) setAlive(x, y) else setDead(x, y)
    }

    companion object {
        @JvmField
        var GILDER_GUN_80x80 = arrayOf(
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ),
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ),
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
                0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ),
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
                0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ),
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
                0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
            ),
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1,
                0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
            ),
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0,
                0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ),
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ),
            intArrayOf(
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            ),
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 },
            IntArray(80) { 0 }, IntArray(80) { 0 }, IntArray(80) { 0 }
        )
    }

}