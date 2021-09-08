package structures.stacks

import java.util.Stack
import kotlin.test.assertEquals

fun main() {
    assertEquals(5,     evaluate("2 3 +"))
    assertEquals(-1,    evaluate("2 -3 +"))
    assertEquals(1,     evaluate("1"))
    assertEquals(-1,    evaluate("-1"))
    assertEquals(1,     evaluate("3 2 -"))
    assertEquals(10,    evaluate("2 3 9 4 / + *"))
    assertEquals(0,     evaluate("3 4 9 / *"))
    assertEquals(3,     evaluate("4 8 + 6 5 - * 3 2 - 2 2 + * /"))
}

fun evaluate(expr: String): Long {
    val stack = Stack<Long>()
    for (s in expr.split(" ".toRegex()).toTypedArray()) {
        when (s) {
            "+" -> stack.push(  stack.pop() + stack.pop())
            "-" -> stack.push( -stack.pop() + stack.pop())
            "*" -> stack.push(  stack.pop() * stack.pop())
            "/" -> {
                val b = stack.pop()
                stack.push(stack.pop() / b)
            }
            else -> stack.push(s.toLong())
        }
    }
    return stack.pop()
}