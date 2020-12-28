package Program

class Simulation(private var board: Array<IntArray>) {
    @JvmField
    var width: Int = board[0].size

    @JvmField
    var height: Int = board.size

    fun setAlive(r: Int, c: Int) {
        if (r < 0 || r >= height || c < 0 || c >= width) return
        board[r][c] = 1
    }

    fun setDead(r: Int, c: Int) {
        if (r < 0 || r >= height || c < 0 || c >= width) return
        board[r][c] = 0
    }

    private fun countAliveNeighbours(r: Int, c: Int): Int {
        var count = 0
        count += getCellValue(r - 1, c - 1)
        count += getCellValue(r, c - 1)
        count += getCellValue(r + 1, c - 1)

        count += getCellValue(r + 1, c)
        count += getCellValue(r - 1, c)

        count += getCellValue(r - 1, c + 1)
        count += getCellValue(r, c + 1)
        count += getCellValue(r + 1, c + 1)

        return count
    }

    fun getCellValue(r: Int, c: Int): Int {
        if (r < 0 || r >= height) return 0
        return if (c < 0 || c >= width) 0
        else board[r][c]
    }

    fun step() {
        val newBoard = Array(height) { IntArray(width) }
        for (r in 0 until height) {
            for (c in 0 until width) {
                val aliveNeighbours = countAliveNeighbours(r, c)
                if (getCellValue(r, c) == 1) {
                    if (aliveNeighbours < 2) {
                        newBoard[r][c] = 0
                    } else if (aliveNeighbours == 2 || aliveNeighbours == 3) {
                        newBoard[r][c] = 1
                    } else {
                        newBoard[r][c] = 0
                    }
                } else if (aliveNeighbours == 3) {
                    newBoard[r][c] = 1
                }
            }
        }
        board = newBoard
    }

    fun toggleState(r: Int, c: Int) {
        if (getCellValue(r, c) == 0) setAlive(r, c) else setDead(r, c)
    }


    companion object {
        private const val size: Int = 148

        private fun getLives(x: Int, rotate: Boolean, shift: Int, vararg indices: Int): Int {
            val y = x - shift
            return if (indices.contains(if (rotate) size - y else y)) 1 else 0
        }

        private fun gliderGun(rotate: Boolean, shift: Int = 0) = arrayOf(
            IntArray(size) { getLives(it, rotate, shift, 74) },
            IntArray(size) { getLives(it, rotate, shift, 72, 74) },
            IntArray(size) { getLives(it, rotate, shift, 62, 63, 70, 71, 84, 85) },
            IntArray(size) { getLives(it, rotate, shift, 61, 65, 70, 71, 84, 85) },
            IntArray(size) { getLives(it, rotate, shift, 50, 51, 60, 66, 70, 71) },
            IntArray(size) { getLives(it, rotate, shift, 50, 51, 60, 64, 66, 67, 72, 74) },
            IntArray(size) { getLives(it, rotate, shift, 60, 66, 74) },
            IntArray(size) { getLives(it, rotate, shift, 61, 65) },
            IntArray(size) { getLives(it, rotate, shift, 62, 63) },
        )

        private val EMPTY_BLOCK = Array(26) { IntArray(size) { 0 } }

        @JvmField
        val DEFAULT_STARTER = arrayOf(
            *EMPTY_BLOCK,
            *gliderGun(true, 25),
            *EMPTY_BLOCK, *EMPTY_BLOCK,
            *gliderGun(false),
            *EMPTY_BLOCK, *EMPTY_BLOCK,
        )
    }

}