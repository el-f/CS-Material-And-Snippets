package structures.trees

// A recursive java program to print reverse level order traversal
// A binary tree node
// Driver program to test above functions
fun main() {
    val tree = TreeForReverse()

    // Let us create trees shown in above diagram
    tree.root = Node(1)
    tree.root!!.left = Node(2)
    tree.root!!.right = Node(3)
    tree.root!!.left.left = Node(4)
    tree.root!!.left.right = Node(5)
    println("Level Order traversal of binary tree is : ")
    tree.reverseLevelOrder(tree.root)
}

internal class TreeForReverse {
    var root: Node? = null

    /* Function to print REVERSE level order traversal a tree*/
    fun reverseLevelOrder(node: Node?) {
        val h = height(node)
        var i: Int = h
        while (i >= 1) {
            printGivenLevel(node, i)
            i--
        }
    }

    /* Print nodes at a given level */
    private fun printGivenLevel(node: Node?, level: Int) {
        if (node == null) return
        if (level == 1) print(node.value.toString() + " ")
        else if (level > 1) {
            printGivenLevel(node.left, level - 1)
            printGivenLevel(node.right, level - 1)
        }
    }

    /* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
    fun height(node: Node?): Int {
        return if (node == null) 0
        else {
            /* compute the height of each subtree */
            val lheight = height(node.left)
            val rheight = height(node.right)

            /* use the larger one */if (lheight > rheight) lheight + 1 else rheight + 1
        }
    }
}