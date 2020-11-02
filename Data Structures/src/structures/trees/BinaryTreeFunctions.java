package structures.trees;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;


class RunExample {

    public static void main(String[] args) {
//        Node root = Node.buildTree('M', new Node('H'), new Node('B'));
//        root.left.left = new Node('S');
//        root.left.left.right = new Node('Q');
//        root.left.left.right.left = new Node('R');
//        root.right.left = new Node('F');
//        root.right.left.right = new Node('C');
//        root.right.right = new Node('L');
//
//        BinaryTree.traverseInOrder(root);

        Node node = Node.sampleTree;
        BinaryTreeFunctions.add('A', node);
        BinaryTreeFunctions.chr = true;
        BinaryTreeFunctions.traverseInOrder(node);
    }
}

@SuppressWarnings({"unused", "RedundantSuppression"})
public abstract class BinaryTreeFunctions {

    public static boolean chr;

    public static Node addRecursive(Node current, int value) {
        if (current == null) return new Node(value);

        if (value < current.value)
            current.left = addRecursive(current.left, value);
        else if (value > current.value)
            current.right = addRecursive(current.right, value);
        else
            return current; // value already exists

        return current;
    }

    public static void add(int value, Node root) {
        if (root == null)
            root = new Node(value);
        Node current = root;
        Node parent = root;
        while (current != null) {
            parent = current;
            if (value < current.value)
                current = current.left;
            else
                current = current.right;
        }
        if (parent.left == null)
            parent.left = new Node(value);
        else parent.right = new Node(value);
    }

    public static boolean containsNodeRecursive(Node current, int value) {
        if (current == null) return false;
        if (value == current.value) return true;

        return value < current.value
                ? containsNodeRecursive(current.left, value)
                : containsNodeRecursive(current.right, value);
    }

    public static boolean containsNode(int value, Node root) {
        Node current = root;
        while (current != null) {
            if (current.value == value)
                return true;
            else if (value < current.value)
                current = current.left;
            else current = current.right;
        }
        return false;
    }

    public static Node deleteRecursive_Naive(Node current, int value) {
        if (current == null) return null;

        if (value == current.value)
            current.value = 0;

        if (value < current.value) {
            current.left = deleteRecursive_Naive(current.left, value);
            return current;
        }
        current.right = deleteRecursive_Naive(current.right, value);
        return current;
    }

    /* A recursive function to insert a new key in BST */
    Node deleteRec(Node node, int key) {
        /* Base Case: If the tree is empty */
        if (node == null) return null;

        /* Otherwise, recur down the tree */
        if (key < node.value)
            node.left = deleteRec(node.left, key);
        else if (key > node.value)
            node.right = deleteRec(node.right, key);

            // if key is same as root's key, then This is the node
            // to be deleted
        else {
            // node with only one child or no child
            if (node.left == null)
                return node.right;
            else if (node.right == null)
                return node.left;

            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            node.value = findSmallestValue_REC(node.right);

            // Delete the inorder successor
            node.right = deleteRec(node.right, node.value);
        }

        return node;
    }

    public static int findSmallestValue_REC(Node root) {
        return root.left == null ? root.value : findSmallestValue_REC(root.left);
    }

    public static int findSmallestValue(Node root) {
        if (root != null) {
            while (root.left != null) {
                root = root.left;
            }
            return root.value;
        }
        return Integer.MAX_VALUE;
    }

    public static int findBiggestValue_Rec(Node root) {
        return root.right == null ? root.value : findBiggestValue_Rec(root.right);
    }

    public static int findBiggestValue(Node root) {
        if (root != null) {
            while (root.right != null) {
                root = root.right;
            }
            return root.value;
        }
        return Integer.MIN_VALUE;
    }

    public static void traversePreOrder(Node node) {
        if (node != null) {
            System.out.print(chr ? " " + (char) node.value : " " + node.value);
            traversePreOrder(node.left);
            traversePreOrder(node.right);
        }
    }

    public static void traverseInOrder(Node node) {
        if (node != null) {
            traverseInOrder(node.left);
            System.out.print(chr ? " " + (char) node.value : " " + node.value);
            traverseInOrder(node.right);
        }
    }

    public static void traversePostOrder(Node node) {
        if (node != null) {
            traversePostOrder(node.left);
            traversePostOrder(node.right);
            System.out.print(chr ? " " + (char) node.value : " " + node.value);
        }
    }

    public static void traverseLevelOrder(Node _root) {
        if (_root == null) return;
        Queue<Node> nodes = new LinkedList<>();
        nodes.add(_root);

        while (!nodes.isEmpty()) {
            Node node = nodes.remove();
            System.out.print(chr ? " " + (char) node.value : " " + node.value);
            if (node.left != null) nodes.add(node.left);
            if (node.right != null) nodes.add(node.right);
        }
    }

    public static void addToStack(Stack<Node> nodes, Node node) {
        if (node == null) return;
        if (node.left != null) addToStack(nodes, node.left);
        if (node.right != null) addToStack(nodes, node.right);
    }

}

