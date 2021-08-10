package snippets

import java.util.*
import kotlin.test.assertTrue

private fun checkBrackets(input: String): Boolean {
    val stack = Stack<Char>()
    val arr: CharArray = input.toCharArray()
    var index = 0

    while (index < arr.size) {
        val current = arr[index++]
        if (current == '(' || current == '{' || current == '[') stack.push(current) else if (current == ')' || current == '}' || current == ']') {
            if (stack.isEmpty()) {
                // unbalanced, more closing the opening
                return false
            } else {
                val lastOpen = stack.pop() // removes and returns object at top of stack
                // check match
                if (!(current == ')' && lastOpen == '(' || current == ']' && lastOpen == '[' || current == '}' && lastOpen == '{')) {
                    // unmatched brackets
                    return false
                }
            }
        }
    } // while

    // if false: UNBALANCED: more opening than closing brackets
    return stack.isEmpty()
}

fun main() {
    listOf(
         checkBrackets("{}()"),
         checkBrackets("({()})"),
        !checkBrackets("{}("),
         checkBrackets("[]"),
        !checkBrackets("{"),
        !checkBrackets("}"),
        !checkBrackets("{)")
    ).forEach(::assertTrue)
}