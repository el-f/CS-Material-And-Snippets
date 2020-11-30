package snippets

fun main() {
    fizzBuzzV2()
    /*---------*/
    fizzBuzzV1()
}

fun fizzBuzzV2() {
    for (i in 1..100) {
        var str = ""
        if (i % 3 == 0) str += "fizz"
        if (i % 5 == 0) str += "buzz"
        if (str == "") str += i
        println(str)
    }
}

fun fizzBuzzV1() {
    for (i in 1..99) {
        println(fizzy(i))
    }
}

private fun fizzy(num: Int): String {
    val a = 3
    val b = 5
    if (num % a == 0 && num % b == 0) return "fizzbuzz"
    if (num % a == 0) return "fizz"
    return if (num % b == 0) "buzz" else num.toString() + ""
}