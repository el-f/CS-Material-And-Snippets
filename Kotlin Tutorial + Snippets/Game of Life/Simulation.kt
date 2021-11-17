import kotlin.random.Random

class Simulation(private var board: Array<BooleanArray>) {
    val height: Int = board.size
    val width: Int = board[0].size

    fun setAlive(r: Int, c: Int) {
        if (r < 0 || r >= height || c < 0 || c >= width) return
        board[r][c] = true
    }

    fun setDead(r: Int, c: Int) {
        if (r < 0 || r >= height || c < 0 || c >= width) return
        board[r][c] = false
    }

    fun toggleState(r: Int, c: Int) {
        if (getCellValue(r, c) == 0) setAlive(r, c) else setDead(r, c)
    }

    fun setRandom(r: Int, c: Int) {
        if (Random.nextBoolean()) setAlive(r, c) else setDead(r, c)
    }

    private fun countAliveNeighbours(r: Int, c: Int): Int {
        return (getCellValue(r - 1, c - 1) +
                getCellValue(r, c - 1) +
                getCellValue(r + 1, c - 1) +

                getCellValue(r + 1, c) +
                getCellValue(r - 1, c) +

                getCellValue(r - 1, c + 1) +
                getCellValue(r, c + 1) +
                getCellValue(r + 1, c + 1))

    }

    private fun getCellValue(r: Int, c: Int): Int {
        return if (r < 0 || r >= height) 0
        else if (c < 0 || c >= width) 0
        else if (board[r][c]) 1 else 0
    }

    fun isAlive(r: Int, c: Int): Boolean {
        return getCellValue(r, c) == 1
    }

    fun step() {
        val newBoard = Array(height) { BooleanArray(width) }
        for (r in 0 until height) {
            for (c in 0 until width) {
                val aliveNeighbours = countAliveNeighbours(r, c)
                if (isAlive(r, c)) {
                    if (aliveNeighbours < 2) {
                        newBoard[r][c] = false
                    } else newBoard[r][c] = aliveNeighbours == 2 || aliveNeighbours == 3
                } else if (aliveNeighbours == 3) {
                    newBoard[r][c] = true
                }
            }
        }
        board = newBoard
    }

    fun clear() {
        for (r in board.indices)
            for (c in board[r].indices)
                setDead(r, c)
    }

    companion object {
        private const val size: Int = 234

        private fun getLives(x: Int, rotate: Boolean, mirror: Boolean, shift: Int, vararg indices: Int): Boolean {
            val y = x - shift
            var indexes = indices
            if (mirror) indexes += indices.map { size - it - 1 + shift }
            return indexes.contains(if (rotate) size - y else y)
        }

        private fun gliderGun(rotate: Boolean = false, shift: Int = 0, mirror: Boolean = false) = arrayOf(
            BooleanArray(size) { getLives(it, rotate, mirror, shift, 24) },
            BooleanArray(size) { getLives(it, rotate, mirror, shift, 22, 24) },
            BooleanArray(size) { getLives(it, rotate, mirror, shift, 12, 13, 20, 21, 34, 35) },
            BooleanArray(size) { getLives(it, rotate, mirror, shift, 11, 15, 20, 21, 34, 35) },

            BooleanArray(size) { getLives(it, rotate, mirror, shift, 0, 1, 10, 16, 20, 21) },

            BooleanArray(size) { getLives(it, rotate, mirror, shift, 0, 1, 10, 14, 16, 17, 22, 24) },
            BooleanArray(size) { getLives(it, rotate, mirror, shift, 10, 16, 24) },
            BooleanArray(size) { getLives(it, rotate, mirror, shift, 11, 15) },
            BooleanArray(size) { getLives(it, rotate, mirror, shift, 12, 13) },
        )

        @Suppress("SameParameterValue")
        private fun emptyBlock(amount: Int) = Array(amount) { BooleanArray(size) }

        @JvmField
        val DEFAULT_STARTER = arrayOf(
            *gliderGun(mirror = true),
            *emptyBlock(144),
            *gliderGun(mirror = true).reversedArray(),
        )
    }

}