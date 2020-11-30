package structures.stacks

import java.util.*

fun main() {
    val stack: Stack<Int> = Stack()
    for (i in 0..4) {
        stack.push(i)
    }
    println(stack[stack.size - 1])

    stack.forEach { print(it) }.also { println() }
    for (i in 0..3) {
        stack.pop()
    }
    val i = stack.pop()
    println(i)
}

fun getN(stack: Stack<Int>, n: Int): Int {
    var a = 0
    val s2: Stack<Int> = Stack()
    for (i in 0 until n - 1) {
        a = stack.pop()
        s2.push(a)
    }
    for (i in 0 until n - 1) {
        stack.push(s2.pop())
    }
    return a
}