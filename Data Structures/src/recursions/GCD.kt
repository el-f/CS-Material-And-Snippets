package recursions

fun main() {
    println(calcGCD(40, 25))
}

/*
 *  ----Greatest Common Divisor----
 *  T(x,y) = c + T(y,x%y) = kc + T(x%y,y%[x%y]) =
 *  = kc + T(y%[x%y],(x%y)%(y%[x%y])) = ... =
 *
 */
fun calcGCD(big: Int, small: Int): Int {
    return if (big % small == 0) small
    else calcGCD(small, big % small)
}