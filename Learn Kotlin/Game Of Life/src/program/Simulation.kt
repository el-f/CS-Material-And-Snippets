package program

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
        return if (r < 0 || r >= height) 0
        else if (c < 0 || c >= width) 0
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

    fun clear() {
        for (r in board.indices)
            for (c in board[r].indices)
                setDead(r, c)
    }

    fun toggleState(r: Int, c: Int) {
        if (getCellValue(r, c) == 0) setAlive(r, c) else setDead(r, c)
    }


    companion object {
        private const val size: Int = 234

        private fun getLives(x: Int, rotate: Boolean, mirror: Boolean, shift: Int, vararg indices: Int): Int {
            val y = x - shift
            var indexes = indices
            if (mirror) indexes += indices.map { size - it - 1 + shift }
            return if (indexes.contains(if (rotate) size - y else y)) 1 else 0
        }

        private fun gliderGun(rotate: Boolean = false, shift: Int = 0, mirror: Boolean = false) = arrayOf(
            IntArray(size) { getLives(it, rotate, mirror, shift, 24) },
            IntArray(size) { getLives(it, rotate, mirror, shift, 22, 24) },
            IntArray(size) { getLives(it, rotate, mirror, shift, 12, 13, 20, 21, 34, 35) },
            IntArray(size) { getLives(it, rotate, mirror, shift, 11, 15, 20, 21, 34, 35) },

            IntArray(size) { getLives(it, rotate, mirror, shift, 0, 1, 10, 16, 20, 21) },

            IntArray(size) { getLives(it, rotate, mirror, shift, 0, 1, 10, 14, 16, 17, 22, 24) },
            IntArray(size) { getLives(it, rotate, mirror, shift, 10, 16, 24) },
            IntArray(size) { getLives(it, rotate, mirror, shift, 11, 15) },
            IntArray(size) { getLives(it, rotate, mirror, shift, 12, 13) },
        )

        private fun emptyBlock(amount: Int) = Array(amount) { IntArray(size) { 0 } }

        @JvmField
        val DEFAULT_STARTER = arrayOf(
            *gliderGun(mirror = true),
            *emptyBlock(144),
            *gliderGun(mirror = true).reversedArray(),
        )
    }

}