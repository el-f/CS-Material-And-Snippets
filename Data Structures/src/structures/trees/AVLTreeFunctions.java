package structures.trees;

import static structures.trees.Node.*;

@SuppressWarnings({"unused", "RedundantSuppression"})
public abstract class AVLTreeFunctions extends BinaryTreeFunctions {

    public boolean isValid(Node root) {
        if (root == null) return true;
        if (Math.abs(height(root.left) - height(root.right)) <= 1)
            return isValid(root.left) && isValid(root.right);
        return false;
    }

    void updateHeight(Node n) {
        n.height = 1 + Math.max(height(n.left), height(n.right));
    }

    int getBalance(Node n) {
        return (n == null) ? 0 : height(n.right) - height(n.left);
    }

    public Node rotateRight(Node node) {
        Node x = node.left;
        Node z = x.right;
        x.right = node;
        node.left = z;
        updateHeight(node);
        updateHeight(x);
        return x;
    }

    public Node rotateLeft(Node node) {
        Node x = node.right;
        Node z = x.left;
        x.left = node;
        node.right = z;
        updateHeight(node);
        updateHeight(x);
        return x;
    }

    Node reBalance(Node z) {
        updateHeight(z);
        int balance = getBalance(z);
        if (balance > 1) {
            if (height(z.right.right) <= height(z.right.left)) {
                z.right = rotateRight(z.right);
            }
            z = rotateLeft(z);
        } else if (balance < -1) {
            if (height(z.left.left) <= height(z.left.right)) {
                z.left = rotateLeft(z.left);
            }
            z = rotateRight(z);
        }
        return z;
    }

    public Node insert(Node node, int value) {
        if (node == null) {
            return new Node(value);
        } else if (node.value > value) {
            node.left = insert(node.left, value);
        } else if (node.value < value) {
            node.right = insert(node.right, value);
        } else {
            throw new RuntimeException("duplicate value!");
        }
        return reBalance(node);
    }

    static Node getMostLeft(Node root) {
        return root == null ? null :
                root.left == null ? root :
                        getMostLeft(root.left);

    }

    public Node delete(Node node, int value) {
        if (node == null) {
            return null;
        } else if (node.value > value) {
            node.left = delete(node.left, value);
        } else if (node.value < value) {
            node.right = delete(node.right, value);
        } else {
            if (node.left == null || node.right == null) {
                node = (node.left == null) ? node.right : node.left;
            } else {
                Node mostLeftChild = getMostLeft(node.right);
                node.value = mostLeftChild.value;
                node.right = delete(node.right, node.value);
            }
        }
        if (node != null) {
            node = reBalance(node);
        }
        return node;
    }

    Node find(Node root, int value) {
        Node current = root;
        while (current != null) {
            if (current.value == value) {
                break;
            }
            current = current.value < value ? current.right : current.left;
        }
        return current;
    }

}
