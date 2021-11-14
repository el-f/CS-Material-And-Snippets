package tutorial._1_2_3

fun main() {
    println(
        "${1.and(0)}\n" +
                "${1.or(0)}\n" +
                "${1.xor(0)}\n" +
                "${3.inv()}\n" +
                "0x${Integer.toHexString(0xf2f7.and(0x51f8))}\n" +
                "${1.coerceAtLeast(4)}\n" +
                "${6.rem(4)}\n" +
                "${100.dec()}\n" +
                "${1.shl(3)}\n" +
                "${8.shr(2)}\n" +
                "${(-18).ushr(0x4)}\n" +
                "${18.ushr(0x4)}"
    )
    println(8 xor 15) //infix
    1.rangeTo(15).forEach { print("$it ") }
    println()
    5.downTo(1).forEach(::print)
}
