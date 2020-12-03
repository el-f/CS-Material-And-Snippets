package recursions

data class Flower(val name: String, val beauty: Int, val price: Int)

/*
 * Implement the optimize_flowers_selection (flowers, budget) function,
 * which receives the flowers - the list of flowers available in the nursery and
 * the budget. The list of flowers is a list of tuples with three values (in order):
 * a string representing the name of the flower, the aesthetic value, and the cost
 * of the flower. The budget is a whole non-negative value. The function returns
 * a tuple with the maximum cumulative aesthetic value given the budget and the
 * rest of the budget (see run example). Please note, the same flower cannot be
 * selected more than once (there is one unit per flower in the nursery).
 */

// ---------- TESTS ---------- //

fun main() {
    //  (2, 0)
    val flowers1 = listOf(
        Flower("Lilac", 1, 3),
        Flower("Hibiscus", 2, 4)
    )

    // (6, 1)
    val flowers2 = listOf(
        Flower("Lilac", 4, 3),
        Flower("Hibiscus", 2, 5),
        Flower("Tulip", 1, 1),
        Flower("Sunflower", 5, 2),
        Flower("Rose", 3, 4)
    )

    // (5, 0)
    val flowers3 = listOf(
        Flower("Lilac", 4, 3),
        Flower("Hibiscus", 2, 5),
        Flower("Tulip", 1, 1)
    )

    println(optimize_flowers_selection(flowers1, 4))
    println(optimize_flowers_selection(flowers2, 4))
    println(optimize_flowers_selection(flowers3, 4))
}

// ---------- SOLUTION ---------- //

val results: MutableList<Pair<Int, Int>> = ArrayList()

fun optimize_flowers_selection(flowers: List<Flower>, budget: Int): Pair<Int, Int> {
    results.clear()
    ofs_helper(flowers, 0, budget)
    return if (results.isEmpty()) Pair(-1, -1) else results.sortedByDescending { it.first }[0]
}

fun ofs_helper(flowers: List<Flower>, beauty: Int, budget: Int) {
    if (flowers.none { it.price <= budget }) results.add(Pair(beauty, budget)).also { return }

    flowers.forEach {
        if (it.price <= budget) {
            ofs_helper(flowers - it, it.beauty + beauty, budget - it.price)
        }
    }

}