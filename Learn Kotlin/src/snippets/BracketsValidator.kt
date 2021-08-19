package snippets

import java.util.*
import kotlin.test.assertTrue

private fun checkBrackets(input: String): Boolean {
    val brackets = mapOf('(' to ')', '[' to ']', '{' to '}')
    val stack = Stack<Char>()

    input.toCharArray().forEach {
        if (it in brackets)                     // is opening bracket
            stack.push(it)
        else if (it in brackets.values)         // closing bracket
            if (stack.isEmpty() ||              // more closing than opening
                brackets[stack.pop()] != it     // unmatched brackets
            ) return false
    }

    // if more opening than closing brackets then false
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