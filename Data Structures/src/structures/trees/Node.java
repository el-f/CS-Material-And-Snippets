package structures.trees;

public class Node {
    public static final Node sampleTree = new Node(
            'T',
            new Node(
                    'Q',
                    new Node('R'),
                    new Node(
                            'B',
                            new Node('W'),
                            null
                    )
            ),
            new Node('L',
                    null,
                    new Node('M',
                            new Node('N', new Node('S'),
                                    new Node('H',
                                            new Node('I', null, new Node('F')),
                                            null
                                    )
                            ),
                            null
                    )
            )
    );


    public int height;
    public int value;
    public Node left;
    public Node right;

    public Node(int value) {
        this.value = value;
        right = null;
        left = null;
        height = 1;
    }

    public Node(int _value, Node _left, Node _right) {
        value = _value;
        left = _left;
        right = _right;
    }

    public static int height(Node node) {
        return node == null
                ? 0
                : 1 + Math.max(height(node.left), height(node.right));
    }

    public static void updateHeights(Node node) {
        if (node == null) return;
        node.height = height(node);
        updateHeights(node.left);
        updateHeights(node.right);
    }

    public static boolean isEmpty(Node node) {
        return node == null;
    }

    public static Node buildTree(int value, Node left, Node right) {
        Node node = new Node(value);
        node.height = 2;
        node.left = left;
        node.right = right;
        return node;
    }
}
