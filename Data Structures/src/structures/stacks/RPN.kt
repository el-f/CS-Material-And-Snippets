package structures.stacks

import java.util.*

fun main() {
    calculateRPN("111++")        //3
    calculateRPN("323+-")        //2
    calculateRPN("352*+")        //13
    calculateRPN("352*+63*+")    //31
}

fun calculateRPN(string: String) {
    val stack = Stack<Int>()
    string.forEach {
        if (it.isDigit())
            stack.push(Character.getNumericValue(it))
        else if (isOperator(it) && !stack.isEmpty())
            stack.push(calc(stack.pop(), stack.pop(), it))
    }
    println(
            if (stack.size == 1) stack.pop()
            else "ERROR"
    )
}

fun calc(num1: Int, num2: Int, operator: Char): Int {
    return when (operator) {
        '*' -> num1 * num2
        '+' -> num1 + num2
        '-' -> num1 - num2
        '/' -> num1 / num2
        else -> throw Exception("Unexpected Operator: $operator")
    }
}

fun isOperator(char: Char) = char == '*' || char == '+' || char == '-' || char == '/'
