package structures.trees

import java.lang.StringBuilder

fun main() {
    println(printVisually(Node.sampleTree))
}

fun printVisually(root: Node): String {
    return printVisually(root, StringBuilder(), true, StringBuilder()).toString()
}

fun printVisually(current: Node, prefix: StringBuilder?, isTail: Boolean, sb: StringBuilder): StringBuilder {
    if (current.right != null) {
        printVisually(
            current.right,
            StringBuilder().append(prefix).append(if (isTail) "│   " else "    "),
            false,
            sb
        )
    }
    sb.append(prefix).append(if (isTail) "└── " else "┌── ").append(current.value.toChar()).append("\n")
    if (current.left != null) {
        printVisually(
            current.left,
            StringBuilder().append(prefix).append(if (isTail) "    " else "│   "),
            true,
            sb
        )
    }
    return sb
}