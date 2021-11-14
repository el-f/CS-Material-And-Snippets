package tutorial._1_2_3


const val str = "wow"
var greeting: String? = null
var num = 3
var boo = true

fun tttt(x: String): Unit {
    println(x)
    val tes1 = JavaClass()
    println(tes1.num)
    println(tes1.string)
}

@Suppress("SENSELESS_NULL_IN_WHEN")
fun main() {

    tttt("bitch ")
    val greetingToPrint = if (greeting != null) greeting else "hi"
    println(greetingToPrint)
    if (boo)
        println(num * 10000)
    when (str) {
        null -> println("ERORRRRR")
        "test" -> println("hmmm")
        else -> println(str)
    }

    fun getGreeting(): String { //fun inside of fun
        fun nested() {
            fun tmp() {
                fun temp() {
                    fun t() {
                        fun zzz() {}
                    }
                }
            }
        }

        return "Hello!"
    }

    fun getHello(): String = "HELLLLO" //single expression func
    fun getHello2() = "HELLLLO ${getHello()} " + getHello() //single expression func

    println(getHello())

    println(getHello2())

    fun sayShit() {
        println("shit")
    }
    sayShit()
    println(getGreeting())
}


