package structures.trees


fun main() {
    val node = Node.buildTree(
        'a'.toInt(),
        Node.buildTree(
            'b'.toInt(),
            Node('d'.toInt()),
            Node('e'.toInt())
        ),
        Node.buildTree(
            'c'.toInt(),
            null,
            Node.buildTree(
                'f'.toInt(),
                Node('g'.toInt()),
                null
            )
        )
    )
    BinaryTreeFunctions.chr = true
    BinaryTreeFunctions.traversePreOrder(node)
    println()
    BinaryTreeFunctions.traverseInOrder(node)
    println()
    BinaryTreeFunctions.traversePostOrder(node)
    println("\n~~~")
    val Q3 = Node.sampleTree
    BinaryTreeFunctions.traversePreOrder(Q3)
    println()
    BinaryTreeFunctions.traverseInOrder(Q3)
    println()
    BinaryTreeFunctions.traversePostOrder(Q3)
    println()
    BinaryTreeFunctions.traverseLevelOrder(Q3)
    println()
}