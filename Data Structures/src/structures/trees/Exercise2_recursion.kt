package structures.trees

import kotlin.math.max

fun main() {
    println(countLeaves(Node.sampleTree))
    printLeaves(Node.sampleTree) //Q1
    println()
    println(countNonLeaves(Node.sampleTree)) //Q2
    println(getDepth(Node.sampleTree)) //Q3
    println(getDepth(Node(1))) //Q3
    println(getMaxValue(Node.sampleTree).toChar()) //Q4
    println(isRouteWeightEqualW(Node.sampleTree, ('T' + 'Q'.toInt() + 'R'.toInt()).toInt(), 0)) //Q5
    println(isRouteWeightEqualW_V2(Node.sampleTree, ('T' + 'Q'.toInt() + 'R'.toInt()).toInt())) //Q5
}

fun countLeaves(root: Node?): Int {
    if (root == null) return 0
    return if (root.right == null && root.left == null) 1
    else countLeaves(root.left) + countLeaves(root.right)
}

//Q1
fun printLeaves(root: Node?) {
    if (root == null) return
    if (root.left == null && root.right == null) System.out.printf("%c ", root.value)
    printLeaves(root.left)
    printLeaves(root.right)
}

//Q2
fun countNonLeaves(root: Node?): Int {
    return if (root == null || root.right == null && root.left == null) 0
    else 1 + countNonLeaves(root.left) + countNonLeaves(root.right)
}

//Q3
fun getDepth(root: Node?): Int {
    return if (root == null) 0 else 1 + max(
        getDepth(root.right),
        getDepth(root.left)
    )
}

//Q4
fun getMaxValue(root: Node?): Int {
    return if (root == null) Int.MIN_VALUE
    else max(
        max(getMaxValue(root.left), getMaxValue(root.right)),
        root.value
    )
}

//Q5
fun isRouteWeightEqualW(root: Node?, w: Int, sumIn: Int): Boolean {
    var sum = sumIn
    if (root == null) return sum == w
    sum += root.value
    return isRouteWeightEqualW(root.left, w, sum) || isRouteWeightEqualW(root.right, w, sum)
}

fun isRouteWeightEqualW_V2(root: Node?, w: Int): Boolean {
    return if (root == null) w == 0
    else isRouteWeightEqualW_V2(root.left, w - root.value) ||
            isRouteWeightEqualW_V2(root.right, w - root.value)
}