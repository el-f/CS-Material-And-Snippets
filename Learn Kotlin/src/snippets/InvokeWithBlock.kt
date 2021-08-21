package snippets


data class Box(var x: Int, var y: Int, var width: Int, var height: Int) {
    fun area() = width * height
    fun rightDown() = width + x to height + y
    fun rightUp() = width + x to height
    fun leftDown() = width to (height + y)
//    operator fun invoke(block: Box.() -> Unit) = apply { block() }
}

operator fun Box.invoke(block: Box.() -> Unit) = apply { block() }

fun main() {
    val box = Box(0, 0, 3, 4)
    box {
        println(area()) // box.area()
        println(width)
        width += 1 // box.width is increased by 1
        println(width)
    }
}




