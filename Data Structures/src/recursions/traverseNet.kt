package recursions

import kotlin.math.abs

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
    println("num of tracks for grid1: " + get_number_legit_tracks(grid1, 0, 0))

    val grid2 = arrayOf(
        intArrayOf(0, 0, 2),
        intArrayOf(1, 0, 4),
        intArrayOf(2, 3, 20)
    )
    println("num of tracks for grid2: " + get_number_legit_tracks(grid2, 1, 0))
}

fun is_legit_track(grid: Array<IntArray>, i1: Int, j1: Int, i2: Int, j2: Int, current_weight: Int): Boolean {
    return if (i2 < 0 || j2 < 0 || i2 >= grid.size || j2 >= grid[0].size) false
    else if (abs(i1 - i2) != 1 && abs(j1 - j2) != 0 && abs(j1 - j2) != 1 && abs(i1 - i2) != 0) false
    else current_weight + grid[i2][j2] >= 0 && current_weight < grid[i2][j2]

}

fun get_number_legit_tracks(grid: Array<IntArray>, i1: Int, j1: Int): Int {
    if (i1 == grid.size - 1 && j1 == grid[0].size - 1) return 1
    var tracks = 0
    val current_weight = grid[i1][j1]
    grid[i1][j1] = 0
    if (is_legit_track(grid, i1, j1, i1 + 1, j1, current_weight)) { //  DOWN
        grid[i1 + 1][j1] += current_weight
        tracks += get_number_legit_tracks(grid, i1 + 1, j1)
        grid[i1 + 1][j1] -= current_weight
    }
    if (is_legit_track(grid, i1, j1, i1 - 1, j1, current_weight)) { //  UP
        grid[i1 - 1][j1] += current_weight
        tracks += get_number_legit_tracks(grid, i1 - 1, j1)
        grid[i1 - 1][j1] -= current_weight
    }
    if (is_legit_track(grid, i1, j1, i1, j1 + 1, current_weight)) { // RIGHT
        grid[i1][j1 + 1] += current_weight
        tracks += get_number_legit_tracks(grid, i1, j1 + 1)
        grid[i1][j1 + 1] -= current_weight
    }
    if (is_legit_track(grid, i1, j1, i1, j1 - 1, current_weight)) { // LEFT
        grid[i1][j1 - 1] += current_weight
        tracks += get_number_legit_tracks(grid, i1, j1 - 1)
        grid[i1][j1 - 1] -= current_weight
    }
    grid[i1][j1] = current_weight
    return tracks
}