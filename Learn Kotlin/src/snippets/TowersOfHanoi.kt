package snippets

const val N = 3 // Number of disks

fun main() = towerOfHanoi(N, 'A', 'C', 'B') // A, B and C are names of rods


fun towerOfHanoi(n: Int, source: Char, destination: Char, helper: Char) {
    if (n == 1) {
        println("Move disk 1 from rod $source to rod $destination")
        return
    }
    towerOfHanoi(n - 1, source, helper, destination)
    println("Move disk $n from rod $source to rod $destination")
    towerOfHanoi(n - 1, helper, destination, source)
}