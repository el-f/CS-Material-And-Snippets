package assignments.III;

import static assignments.III.tNode.*;

@SuppressWarnings({"all", "RedundantSuppression"})
public class Homework3A_Trees {
    /*
        sample tree (not BST but a good tree for testing)

                                   T
                                 /   \
                               Q       L
                             /   \       \
                            R    B         M
                                /         /
                               W        N
                                      /   \
                                     S     H
                                          /
                                         I
                                          \
                                           F
     */
    public static void main(String[] args) {
        //Q1
        System.out.println(countChildren(sampleTree)); //11
        System.out.println(countChildren(sampleTree.left)); //3

        //Q2
        System.out.println(getBalance(sampleTree)); //3
        System.out.println(getBalance(sampleTree.left)); //1

        //Q3
        System.out.println(avgLeafDist(sampleTree)); //3.75
        System.out.println(avgLeafDist(sampleTree.left)); //1.5

        //Q4
        System.out.println((char) getNextInOrder(sampleTree, sampleTree).value); //L (next for T node)
        System.out.println((char) getNextInOrder(sampleTree, sampleTree.left.left).value); //Q (parent of R leaf)

        System.out.println(
                (char) getNextInOrder(
                        sampleTree,
                        sampleTree.right.right.left.right.left.right
                ).value
        ); //H (GRANDPARENT of F leaf)


    }

    //Q1
    static int countChildren(tNode node) {
        if (isEmpty(node)) return 0;
        return countChildren_helper(node) - 1; //not counting head
    }

    private static int countChildren_helper(tNode root) {
        if (isEmpty(root)) return 0;
        return 1 + countChildren_helper(root.left) + countChildren_helper(root.right);
    }


    //Q2
    static int getBalance(tNode node) {
        return Math.abs(height(node.left) - height(node.right));
    }


    //Q3
    static double avgLeafDist(tNode root) {
        if (isEmpty(root) || (isEmpty(root.left) && isEmpty(root.right)))
            return 0;
        return 1 + (avgLeafDist(root.left) + avgLeafDist(root.right)) / div(root);
    }

    private static int div(tNode node) {
        return (!isEmpty(node.left) && !isEmpty(node.right)) ? 2 : 1;
    }


    //Q4
    static tNode getNextInOrder(tNode root, tNode node) {
        if (isEmpty(node) || isEmpty(root)) return null;
        tNode next;

        /* in case of leaf next in order is the parent/grandparent */
        if (isEmpty(node.left) && isEmpty(node.right))
            next = findParent_InOrder(root, root, node, true);
        else {
            next = node.right;
            if (!isEmpty(next))
                while (!isEmpty(next.left))
                    next = next.left;
        }
        return next;
    }

    private static tNode findParent_InOrder(tNode root, tNode currParent, tNode child, boolean skip) {
        if (!isEmpty(currParent) && !isEmpty(child)) {
            tNode parent = chooseLR(root, currParent, child, skip);
            if (parent != null) return parent;
            parent = findParent_InOrder(root, currParent.left, child, skip);
            return parent != null ? parent : findParent_InOrder(root, currParent.right, child, skip);
        }
        return null;
    }

    //skip boolean for case of needing grandparent (INORDER)
    private static tNode chooseLR(tNode root, tNode currParent, tNode child, boolean skip) {
        if (currParent.left == child) return currParent;
        if (currParent.right == child) return skip ? findParent_InOrder(root, root, currParent, false) : currParent;
        return null;
    }

}

class tNode {
    public int value;
    public tNode left;
    public tNode right;

    public tNode(int value) {
        this(value, null, null);
    }

    public tNode(int _value, tNode _left, tNode _right) {
        value = _value;
        left = _left;
        right = _right;
    }

    public static int height(tNode node) {
        return isEmpty(node) ? 0 : 1 + Math.max(height(node.left), height(node.right));
    }

    public static boolean isEmpty(tNode node) {
        return node == null;
    }

    public static final tNode sampleTree = new tNode(
            'T',
            new tNode(
                    'Q',
                    new tNode('R'),
                    new tNode(
                            'B',
                            new tNode('W'),
                            null
                    )
            ),
            new tNode('L',
                    null,
                    new tNode('M',
                            new tNode('N', new tNode('S'),
                                    new tNode('H',
                                            new tNode('I', null, new tNode('F')),
                                            null
                                    )
                            ),
                            null
                    )
            )
    );
}