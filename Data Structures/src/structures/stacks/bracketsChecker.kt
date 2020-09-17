package structures.stacks

import java.util.*

fun main() {
    fun printRes(string: String){
        val result = bracketsChecker(string)
        println("${result.bool} (${result.msg})")
    }
    printRes("{x+[z-(x+y)*x+{y-x}]-(x-y)}")
    printRes("{x+[z-(x+y)*x+{y-x}]-(x-y)")
    printRes("{x+[z-(x+y)*x+{y-x}]-x-y)}")
    printRes("x+[z-(x+y)*x+{y-x}]-(x-y)}")
}



data class BoolMsg(val bool: Boolean, val msg: String)

fun bracketsChecker(string: String): BoolMsg {
    val stack = Stack<Char>()
    string.forEach {
        if (it == '(' || it == '{' || it == '[')
            stack.push(it)
        else if (it == ')' || it == '}' || it == ']') {
            if (stack.isEmpty()) return BoolMsg(false, "unbalanced! more closing the opening!")
            else {
                val lastOpen = stack.pop()
                if (!(it == ')' && lastOpen == '(' ||
                                it == ']' && lastOpen == '[' ||
                                it == '}' && lastOpen == '{'))
                    return BoolMsg(false, "unmatched brackets: $it closes $lastOpen")
            }
        }
    }
    return if (!stack.isEmpty())
        BoolMsg(false, "UNBALANCED: more opening than closing brackets")
    else BoolMsg(true, "OK!")
}