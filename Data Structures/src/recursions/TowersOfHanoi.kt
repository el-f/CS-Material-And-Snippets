package recursions

const val N = 3 // Number of disks

fun main() = towerOfHanoi(N, 'A', 'B', 'C') // A, B and C are names of rods


fun towerOfHanoi(n: Int, source: Char, helper: Char, destination: Char) {
    if (n == 1) {
        println("Move disk 1 from rod $source to rod $destination")
        return
    }
    towerOfHanoi(n - 1, source = source, helper = destination, destination = helper)
    println("Move disk $n from rod $source to rod $destination")
    towerOfHanoi(n - 1, source = helper, helper = source, destination = destination)
}