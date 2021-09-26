package Snippets;

import java.util.HashMap;

// my solution for this kata: 52a89c2ea8ddc5547a000863
public class GetLoopSizeInLinkedList<V> {

    public int loopSize(Node<V> node) {
        HashMap<Node<V>, Integer> map = new HashMap<>();
        int iter = 0;

        while (node != null) {
            if (map.containsKey(node)) return iter - map.get(node);
            map.put(node, iter);
            iter++;
            node = node.getNext();
        }
        return -1;
    }
}

abstract class Node<T> {
    abstract Node<T> getNext();
    abstract T getValue();
}