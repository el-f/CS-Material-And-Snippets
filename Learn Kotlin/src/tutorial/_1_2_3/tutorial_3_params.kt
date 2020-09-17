package tutorial._1_2_3

fun sayHello(greeting: String, itemsToGreet: List<String>) {
    itemsToGreet.forEach { println("$greeting $it") }
}

fun sayHello2(greeting: String, vararg itemsToGreet: String) { //vararg usage
    itemsToGreet.forEach { println("$greeting $it") }
}

fun greet(greeting: String, name: String) = println("$greeting $name")

fun greetWithDefaults(greeting: String = "HELLO THEREEEE", name: String = "def name") =
    println("$greeting $name!")

fun main() {
    val things = listOf("kotlin", "programming", "books")
    val thingsArr = arrayOf("kotlin", "programming", "books")
    sayHello("hello", things)
    sayHello2("Hi", *thingsArr) //spread operator
    println("~~")

    greet("hi", "person")
    greet(name = "senior", greeting = "Holla")
    println("~~")

    greetWithDefaults(name = "idiot")
}
