package snippets

/*
    Solution for:
    5426d7a2c2c7784365000783

    Write a function which makes a list of strings representing all of the ways you can balance n pairs of parentheses

    Examples
    balancedParens(0) returns ArrayList<String> with element:  ""
    balancedParens(1) returns ArrayList<String> with element:  "()"
    balancedParens(2) returns ArrayList<String> with elements: "()()","(())"
    balancedParens(3) returns ArrayList<String> with elements: "()()()","(())()","()(())","(()())","((()))"
 */

fun main() = balancedParens(3).forEach { println(it) }

fun balancedParens(n: Int): List<String> {
    val result: MutableList<String> = ArrayList()
    bpHelper(CharArray(2 * n), n, 0, 0, 0, result)
    return result
}

private fun bpHelper(str: CharArray, n: Int, curr_index: Int, open: Int, close: Int, list: MutableList<String>) {
    if (close == n) {
        list.add(String(str))
    } else {
        if (open > close) {
            str[curr_index] = ')'
            bpHelper(str, n, curr_index + 1, open, close + 1, list)
        }
        if (open < n) {
            str[curr_index] = '('
            bpHelper(str, n, curr_index + 1, open + 1, close, list)
        }
    }
}