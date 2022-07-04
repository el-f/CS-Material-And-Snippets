package structures.trees;

import java.util.*;

public class BinaryTreeLevelSort {

    /*
        52bef5e3588c56132c0003bc
     */

    public static List<Integer> treeByLevels(Node _node) {
        List<Integer> result = new ArrayList<>();
        if (_node == null) return result;

        Queue<Node> nodes = new LinkedList<>();
        nodes.add(_node);
        Node current;
        while (!nodes.isEmpty()) {
            current = nodes.remove();
            result.add(current.value);
            if (current.left != null) nodes.add(current.left);
            if (current.right != null) nodes.add(current.right);
        }

        return result;
    }
}





