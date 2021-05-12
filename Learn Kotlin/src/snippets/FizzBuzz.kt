package snippets

fun main() {
    fizzBuzzV3()
    /*---------*/
//    fizzBuzzV2()
    /*---------*/
//    fizzBuzzV1()

}

fun fizzBuzzV3(dict: Map<Int, String> = mapOf(3 to "fizz", 5 to "buzz")) {
    for (i in 1..100) {
        var str = ""
        for (key in dict.keys)
            if (i % key == 0) str += dict[key]
        println(str.ifEmpty { i })
    }
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