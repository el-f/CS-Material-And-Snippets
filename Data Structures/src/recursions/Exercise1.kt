package recursions

fun main() {
    val a = intArrayOf(1, 2, 3, 4, 5)
    val aNotSorted = intArrayOf(1, 3, 3, 2, 5)
    val arr = intArrayOf(112, 61, 55, 22, 10, 5, 0)
    val s = "abcba"
    println(countDigits(777)) //3
    println(isSorted(a, a.size)) //1
    println(isSorted(aNotSorted, aNotSorted.size)) //0
    println(findNum(arr, 0, arr.size - 1, 22)) //3
    println(countWheels(1)) //4
    println(countWheels(2)) //6
    println(countWheels(3)) //10
    println(isPalindrome(s, s.length)) //1
    print_(5)
    println()
    tnirp(5)
    println()
    upDown(5)
    assert(false)
}

fun countDigits(num: Int): Int {
    return if (num < 10) 1 else countDigits(num / 10) + 1
}

fun isSorted(A: IntArray, n: Int): Int {
    if (n == 2) return 1
    return if (A[n - 1] >= A[n - 2]) isSorted(A, n - 1) else 0
}

//binary search inverse sorted array
fun findNum(A: IntArray, first: Int, last: Int, num: Int): Int {
    if (last >= first) {
        val mid = first + (last - first) / 2
        if (A[mid] == num) return mid
        return if (A[mid] < num)
            findNum(A, first, mid - 1, num)
        else
            findNum(A, mid + 1, last, num)
    }
    return -1 //not present
}

//even places - 2 wheels. odd places - 4 wheels.
fun countWheels(n: Int): Int {
    return if (n <= 1) 4 else n % 2 * 2 + 2 + countWheels(n - 1)
}

fun isPalindrome(S: String, n: Int): Int {
    if (n <= 1) return 1
    return if (S[0] == S[S.length - 1]) isPalindrome(S.substring(1, S.length - 1), n - 2) else 0
}

fun print_(n: Int) {
    if (n == 0) return
    print_(n - 1)
    print("$n ")
}

fun tnirp(n: Int) {
    if (n == 0) return
    print("$n ")
    tnirp(n - 1)
}

fun upDown(n: Int) {
    upDownHelper(n = n)
}

fun upDownHelper(i: Int = 1, n: Int) {
    print("$i ")
    if (i == n) return
    upDownHelper(i + 1, n)
    print("$i ")
}


