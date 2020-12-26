package structures.trees;

public class Exercise1 {
    public static void main(String[] args) {
        Node node = Node.buildTree(
                'a',
                Node.buildTree(
                        'b',
                        new Node('d'),
                        new Node('e')
                ),
                Node.buildTree(
                        'c',
                        null,
                        Node.buildTree(
                                'f',
                                new Node('g'),
                                null
                        )
                )
        );
        BinaryTreeFunctions.chr = true;
        BinaryTreeFunctions.traversePreOrder(node);
        System.out.println();

        BinaryTreeFunctions.traverseInOrder(node);
        System.out.println();

        BinaryTreeFunctions.traversePostOrder(node);
        System.out.println("\n~~~");


        Node Q3 = Node.sampleTree;

        BinaryTreeFunctions.traversePreOrder(Q3);
        System.out.println();

        BinaryTreeFunctions.traverseInOrder(Q3);
        System.out.println();

        BinaryTreeFunctions.traversePostOrder(Q3);
        System.out.println();

        BinaryTreeFunctions.traverseLevelOrder(Q3);
        System.out.println();

    }
}
