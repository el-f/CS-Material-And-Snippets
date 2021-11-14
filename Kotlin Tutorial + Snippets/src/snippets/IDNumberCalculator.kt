package snippets

import java.util.*
import kotlin.math.log10

fun main() = idChecker()

fun idChecker() {
    var idNum = 0
    val s = Scanner(System.`in`)
    while (log10(idNum.toDouble()).toInt() + 1 < 8 || log10(idNum.toDouble()).toInt() + 1 > 9) {
        println("Please enter your ID number:")
        idNum = s.nextInt()
    }
    s.close()

    val inputCheckDigit: Int = idNum % 10
    var tempNum: Int = idNum
    tempNum /= 10

    // Dealing with "8" digit ID's
    val iInit: Int = if (log10(idNum.toDouble()).toInt() + 1 == 9) log10(idNum.toDouble()).toInt()
    // Since number starts at 0, once we remove check digit its shows as 7 digits so
    // we need to add 1 to initialise i at 8 to account for the first 0 (0*1)
    else log10(idNum.toDouble()).toInt() + 1

    var tempDigit: Int
    var idSum = 0
    var digitOpr: Int
    for (i in iInit downTo 1) {
        tempDigit = tempNum % 10
        tempNum /= 10
        digitOpr = ((i + 1) % 2 + 1) * tempDigit
        idSum += if (digitOpr > 9) {
            digitOpr % 10 + digitOpr / 10
        } else {
            digitOpr
        }
    }
    val outputCheckDigit = if (idSum % 10 == 0) 0 else 10 - idSum % 10
    if (inputCheckDigit == outputCheckDigit) println("Proper ID!") else println("Not proper ID!")
}