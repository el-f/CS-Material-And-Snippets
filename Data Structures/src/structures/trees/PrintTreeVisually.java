package structures.trees;

public class PrintTreeVisually {

    public static void main(String[] args) {
        System.out.println(printVisually(Node.sampleTree));
    }
    public static String printVisually(Node root) {
        return printVisually(root, new StringBuilder(), true, new StringBuilder()).toString();
    }

    public static StringBuilder printVisually(Node current, StringBuilder prefix, boolean isTail, StringBuilder sb) {
        if (current.right != null) {
            printVisually(current.right, new StringBuilder().append(prefix).append(isTail ? "│   " : "    "), false, sb);
        }
        sb.append(prefix).append(isTail ? "└── " : "┌── ").append((char) current.value).append("\n");
        if (current.left != null) {
            printVisually(current.left, new StringBuilder().append(prefix).append(isTail ? "    " : "│   "), true, sb);
        }
        return sb;
    }
}
