package snippets

// 0 - new constructors
operator fun Int.Companion.invoke(s: String): Int = s.toInt()
operator fun Long.Companion.invoke(s: String): Long = s.toLong()
operator fun Double.Companion.invoke(s: String): Double = s.toDouble()

// 1 - invoking strings
operator fun <T> String.invoke(x: T) = x

// 2 - opposite methods
inline fun until(b: () -> Boolean, action: () -> Unit) {
    while (!b()) action()
}

// 3
data class Box(var x: Int, var y: Int, var width: Int, var height: Int) {
    fun area() = width * height
    fun rightDown() = width + x to height + y
    fun rightUp() = width + x to height
    fun leftDown() = width to (height + y)
//    operator fun invoke(block: Box.() -> Unit) = apply { block() }
}

operator fun Box.invoke(block: Box.() -> Unit) = apply { block() }

fun main() {
    println(Int("42"))
    println("hello"("world"))
    var i = 3
    until({ i == 0 }) {
        print("${i--} ")
    }

    println()

    val box = Box(0, 0, 3, 4)
    box {
        println(area()) // box.area()
        println(width)
        width += 1 // box.width is increased by 1
        println(width)
    }
}




