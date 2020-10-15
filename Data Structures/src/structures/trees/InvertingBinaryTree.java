package structures.trees;

/*
    Invert a binary tree.

    Input:

         4
       /   \
      2     7
     / \   / \
    1   3 6   9

    Output:

         4
       /   \
      7     2
     / \   / \
    9   6 3   1

    Trivia:
    This problem was inspired by this original tweet by Max Howell:

    Google: 90% of our engineers use the software you wrote (Homebrew),
    but you can’t invert a binary tree on a whiteboard so f*** off.

 */

import java.util.LinkedList;
import java.util.Queue;

public class InvertingBinaryTree {

    /*
        ---[ Recursive Approach ]---

            Complexity Analysis:

            Since each node in the tree is visited only once, the time complexity is O(n),
            where n is the number of nodes in the tree. We cannot do better than that,
            since at the very least we have to visit each node to invert it.

            Because of recursion, O(h) function calls will be placed on the stack in the worst case,
            where h is the height of the tree. Because h∈O(n), the space complexity is O(n).
     */
    public TreeNode invertTreeRec(TreeNode root) {
        if (root == null) {
            return null;
        }
        TreeNode right = invertTreeRec(root.right);
        TreeNode left = invertTreeRec(root.left);
        root.left = right;
        root.right = left;
        return root;
    }

    /*
        ---[ Iterative Approach ]---

            Algorithm

            The idea is that we need to swap the left and right child of all nodes in the tree.
            So we create a queue to store nodes whose left and right child have not been swapped yet.
            Initially, only the root is in the queue. As long as the queue is not empty, remove the next
            node from the queue, swap its children, and add the children to the queue. Null nodes are not
            added to the queue. Eventually, the queue will be empty and all the children swapped,
            and we return the original root.

            Complexity Analysis

            Since each node in the tree is visited / added to the queue only once, the time complexity is O(n),
            where n is the number of nodes in the tree.

            Space complexity is O(n), since in the worst case, the queue will contain all nodes in one level of
            the binary tree. For a full binary tree, the leaf level has ciel(n/2) = O(n) leaves.

     */
    public TreeNode invertTree(TreeNode root) {
        if (root == null) return null;
        Queue<TreeNode> queue = new LinkedList<>();
        queue.add(root);
        while (!queue.isEmpty()) {
            TreeNode current = queue.poll();
            TreeNode temp = current.left;
            current.left = current.right;
            current.right = temp;
            if (current.left != null) queue.add(current.left);
            if (current.right != null) queue.add(current.right);
        }
        return root;
    }

}

class TreeNode {
    int value;
    TreeNode left;
    TreeNode right;

    TreeNode(int value) {
        this.value = value;
    }

    TreeNode(int val, TreeNode left, TreeNode right) {
        this.value = val;
        this.left = left;
        this.right = right;
    }
}