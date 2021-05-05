package structures.trees


fun main() {
    val node = Node.buildTree(
            'a'.code,
            Node.buildTree(
                    'b'.code,
                    Node('d'.code),
                    Node('e'.code)
            ),
            Node.buildTree(
                    'c'.code,
                    null,
                    Node.buildTree(
                            'f'.code,
                            Node('g'.code),
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