package recursions

import java.math.BigInteger

val ONE: BigInteger = BigInteger.ONE
val FIFTY = 50.toBigInteger()

fun main() {
    println(tailFact(FIFTY * FIFTY))
    println(fact(FIFTY * FIFTY))
}

//regular recursion - inefficient
fun fact(n: BigInteger): BigInteger {
    return if (n == ONE) ONE else n * fact(n - ONE)
}

//tail recursion - more efficient
fun tailFact(n: BigInteger, m: BigInteger = ONE): BigInteger {
    return if (n == ONE) m else tailFact(n - ONE, n * m)
}