package structures.trees;

public class Exercise2_recursion {


    public static void main(String[] args) {
        System.out.println(countLeaves(Node.sampleTree));
        printLeaves(Node.sampleTree);                                                            //Q1
        System.out.println();
        System.out.println(countNonLeaves(Node.sampleTree));                                     //Q2
        System.out.println(getDepth(Node.sampleTree));                                           //Q3
        System.out.println(getDepth(new Node(1)));                                   //Q3
        System.out.println((char) getMaxValue(Node.sampleTree));                                 //Q4
        System.out.println(isRouteWeightEqualW(Node.sampleTree, 'T' + 'Q' + 'R', 0));    //Q5
        System.out.println(isRouteWeightEqualW_V2(Node.sampleTree, 'T' + 'Q' + 'R'));         //Q5

    }

    static int countLeaves(Node root) {
        if (root == null) return 0;
        if (root.right == null && root.left == null)
            return 1;
        return countLeaves(root.left) + countLeaves(root.right);
    }

    //Q1
    static void printLeaves(Node root) {
        if (root == null) return;
        if (root.left == null && root.right == null)
            System.out.printf("%c ", root.value);
        printLeaves(root.left);
        printLeaves(root.right);
    }

    //Q2
    static int countNonLeaves(Node root) {
        if (root == null || (root.right == null && root.left == null))
            return 0;
        return 1 + countNonLeaves(root.left) + countNonLeaves(root.right);
    }

    //Q3
    static int getDepth(Node root) {
        if (root == null) return 0;
        return 1 + Math.max(
                getDepth(root.right),
                getDepth(root.left)
        );
    }

    //Q4
    static int getMaxValue(Node root) {
        if (root == null) return Integer.MIN_VALUE;
        return Math.max(
                Math.max(getMaxValue(root.left), getMaxValue(root.right)),
                root.value
        );
    }

    //Q5
    static boolean isRouteWeightEqualW(Node root, int w, int sum) {
        if (root == null) return sum == w;
        sum += root.value;
        return isRouteWeightEqualW(root.left, w, sum) ||
                isRouteWeightEqualW(root.right, w, sum);
    }

    static boolean isRouteWeightEqualW_V2(Node root, int w) {
        if (root == null) return w == 0;
        return isRouteWeightEqualW_V2(root.left, w - root.value) ||
                isRouteWeightEqualW_V2(root.right, w - root.value);
    }


}
