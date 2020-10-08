package Concordance;

public class MyBinarySearchTree {

    private static class MyNode {
        String word;
        MyLinkedList lineNumbers;
        MyNode left;
        MyNode right;

        public MyNode(String _word, int lineNumber) {
            word = _word;
            lineNumbers = new MyLinkedList(lineNumber); //O(1)
            right = null;
            left = null;
        }

        //O(n) when n is the size of the lineNumbers List
        @Override
        public String toString() {
            String separator = " -> ";
            return word + separator + lineNumbers.toString(word.length() + separator.length()) + '\n';
        }
    }

    MyNode root = null;

    /*
        Binary Search
        Average Case: O(lgn + l)
        Worst Case: O(n + l)
        n is the number of words in the tree and l is the number of lines the found word appears in
    */
    public String search(String word) {
        MyNode searchResult = binarySearch(word, root);
        if (searchResult == null) return "Word Not Found!\n";
        return searchResult.toString();
    }

    private MyNode binarySearch(String word, MyNode current) {
        if (current == null) {
            return null;
        }
        int comparison = current.word.compareTo(word);
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
        when n is the total number of words in the tree
    */
    public void insert(String word, int lineNumber) {
        root = insert(root, word, lineNumber);
    }

    private MyNode insert(MyNode current, String word, int lineNumber) {
        if (current == null) {
            current = new MyNode(word, lineNumber);
            return current;
        }
        int comparison = current.word.compareTo(word);
        if (comparison == 0) {
            //In case of same word we just enter the line number into the existing LinkedList after the tail
            current.lineNumbers.insert(lineNumber);
        } else if (comparison > 0) {
            current.left = insert(current.left, word, lineNumber);
        } else {
            current.right = insert(current.right, word, lineNumber);
        }
        return current;
    }

    //O(n) when n is the number of words in the original file
    @Override
    public String toString() {
        return getAllInOrderForTree(root, new StringBuilder()).toString();
    }

    private StringBuilder getAllInOrderForTree(MyNode current, StringBuilder result) {
        if (current == null) return result;
        getAllInOrderForTree(current.left, result);
        result.append(current);
        getAllInOrderForTree(current.right, result);
        return result;
    }

}
