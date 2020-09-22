package snippets


fun main() {
    val wantedPairs = 15

    var num1 = 220 // 220 is the lowest amicable number so no need to calculate below it
    var num2: Int
    var sum1: Int
    var sum2: Int
    var pairs = 0
    var previousPair = 0
    while (pairs < wantedPairs) {
        sum1 = 0
        sum2 = 0
        /*
         * The loop stops already at half the number because proper divisors of a number
         * are always equal to or less than half the number.
         */for (i in 1..num1 / 2) {
            if (num1 % i == 0) sum1 += i
        }
        num2 = sum1
        for (i in 1..num2 / 2) {
            if (num2 % i == 0) sum2 += i
        }
        /*
         * Checking if: The definition applies, The numbers are different from each
         * other, and that we didn't get the pair already.
         */
        if (num1 == sum2 && num2 == sum1 && num1 != num2 && previousPair != num1 + num2) {
            pairs++
            println("$pairs) $num1 and $num2 are mates")
            previousPair = num1 + num2
        }
        num1++
    }
}
