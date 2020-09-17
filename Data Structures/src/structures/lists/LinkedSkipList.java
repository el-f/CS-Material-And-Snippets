package structures.lists;

//SkipList using LinkedList

@SuppressWarnings({"unused", "RedundantSuppression"})
public class LinkedSkipList {
    static class SkipList_Node {
        int data;
        SkipList_Node right, down;
    }

    SkipList_Node search(int value, SkipList_Node node) {
        while (node != null) {
            while (node.right.data <= value)
                node = node.right;

            if (node.data == value) return node;
            else node = node.down;
        }
        return null;
    }
}
