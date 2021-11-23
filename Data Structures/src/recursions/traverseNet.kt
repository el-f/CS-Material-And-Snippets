package recursions

/*
    Ahead of the new season of Ninja Israel, the producers of the show have created a new facility.
    The new device is a kind of climbing wall, built in the shape of a lattice the size of n * m,
    where each cell (i, j) in the lattice contains an item weighing W(i,j), and can support a total weight
    of items smaller than 2*W(i,j) (ignore participant weight). Upon arrival at the cell, the participant
    is required to collect the weight in the cell, and its weight is added to the weight gained so far.
    If the total cumulative weight of the items exceeds the weight threshold supported in the cell,
    the participant falls into the water and is disqualified. The end of the trajectory is defined as
    a cell in position (n-1, m-1), i.e. the last cell in the last row. The facility is built in a
    structure that allows passage only between adjacent cells in the up / down / right / left directions,
    without diagonals. A valid trajectory is defined as a series of transitions between cells in which
    the total cumulative weight of the items does not exceed the supported weight threshold in each of
    the cells along the way.

    You must implement software that receives as input the structure of the trellis,
    the weights in each cell, and a starting cell and returns the number of all legal
    routes from the beginning to the end of the route.
 */

fun main() {
    val grid1 = arrayOf(
        intArrayOf(0, 1, 2),
        intArrayOf(1, 2, 4),
        intArrayOf(2, 4, 8)
    )
    println("num of tracks for grid1: " + numOfValidRoutes(grid1, 0, 0))

    val grid2 = arrayOf(
        intArrayOf(0, 0, 2),
        intArrayOf(1, 0, 4),
        intArrayOf(2, 3, 20)
    )
    println("num of tracks for grid2: " + numOfValidRoutes(grid2, 1, 0))
}

fun isValidStep(
    grid: Array<IntArray>,
    new_r: Int, new_c: Int,
    current_weight: Int
): Boolean {
    return if (new_r < 0 || new_c < 0 || new_r >= grid.size || new_c >= grid[0].size) false
    else current_weight + grid[new_r][new_c] >= 0 && current_weight < grid[new_r][new_c]

}

fun numOfValidRoutes(grid: Array<IntArray>, r: Int, c: Int): Int {
    if (r == grid.size - 1 && c == grid[0].size - 1) return 1
    var tracks = 0
    val currentWeight = grid[r][c]
    grid[r][c] = 0
    if (isValidStep(grid, r + 1, c, currentWeight)) { //  DOWN
        grid[r + 1][c] += currentWeight
        tracks += numOfValidRoutes(grid, r + 1, c)
        grid[r + 1][c] -= currentWeight
    }
    if (isValidStep(grid, r - 1, c, currentWeight)) { //  UP
        grid[r - 1][c] += currentWeight
        tracks += numOfValidRoutes(grid, r - 1, c)
        grid[r - 1][c] -= currentWeight
    }
    if (isValidStep(grid, r, c + 1, currentWeight)) { // RIGHT
        grid[r][c + 1] += currentWeight
        tracks += numOfValidRoutes(grid, r, c + 1)
        grid[r][c + 1] -= currentWeight
    }
    if (isValidStep(grid, r, c - 1, currentWeight)) { // LEFT
        grid[r][c - 1] += currentWeight
        tracks += numOfValidRoutes(grid, r, c - 1)
        grid[r][c - 1] -= currentWeight
    }
    grid[r][c] = currentWeight
    return tracks
}