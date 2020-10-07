package Concordance;

import Concordance.ConcordanceProcessor.Cell;

public class CellsBinarySearchTree {

    static class Node {
        Cell value;
        Node left;
        Node right;

        public Node(Cell value) {
            this.value = value;
            right = null;
            left = null;
        }
    }

    Node root = null;

    /*
        Binary Search
        Average Case: O(lgn + m)
        Worst Case: O(n + m)
        n is the number of words in the tree and m is the number of lines the found word appears in
    */
    public String search(String word) {
        Node searchResult = binarySearch(word, root);
        if (searchResult == null) return "Word Not Found!";
        return searchResult.value.toString();
    }

    private Node binarySearch(String word, Node current) {
        if (current == null) {
            return null;
        }
        int comparison = current.value.word.compareTo(word);
        if (comparison == 0) {
            return current;
        } else if (comparison > 0) {
            return binarySearch(word, current.left);
        }
        return binarySearch(word, current.right);
    }

    /*
        Average Case: O(lgn)
        Worst Case: O(n)
        when n is the number of total words in the tree
    */
    public void insert(Cell cell) {
        root = insert(root, cell);
    }

    private Node insert(Node current, Cell newCell) {
        if (current == null) {
            current = new Node(newCell);
            return current;
        }
        int comparison = current.value.word.compareTo(newCell.word);
        if (comparison == 0) {
            /*
                in case of same word the new cell has only one word in its list
                so we just get it and insert it into the existing list.
             */
            current.value.insert(newCell.lineNumbers.getCurrentVal());
        } else if (comparison > 0) {
            current.left = insert(current.left, newCell);
        } else {
            current.right = insert(current.right, newCell);
        }
        return current;
    }

    //O(n * m) when n is the number of words and m is number of lines the words appears in
    @Override
    public String toString() {
        return getAllInOrderForTree(root, new StringBuilder()).toString();
    }

    private StringBuilder getAllInOrderForTree(Node current, StringBuilder result) {
        if (current == null) return result;
        getAllInOrderForTree(current.left, result);
        result.append(current.value);
        getAllInOrderForTree(current.right, result);
        return result;
    }

}
