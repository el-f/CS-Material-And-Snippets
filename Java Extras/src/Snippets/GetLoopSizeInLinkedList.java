package Snippets;

import java.util.HashMap;

// my solution for this kata: 52a89c2ea8ddc5547a000863

public class GetLoopSizeInLinkedList<V> {

    HashMap<Node<V>, Integer> map = new HashMap<>();

    public int loopSize(Node<V> node) {
        int iter = 0;

        while (true) {
            if (map.containsKey(node)) return iter - map.get(node);
            map.put(node, iter);
            iter++;
            node = node.getNext();
        }

    }
}

abstract class Node<T> {
    abstract Node<T> getNext();

    abstract T getValue();
}
