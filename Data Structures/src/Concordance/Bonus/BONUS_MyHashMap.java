package Concordance.Bonus;

import Concordance.MyLinkedList;

import java.util.Arrays;

// Faster than BST at building but slower at printing/outputing (because outputing sorted)

public class BONUS_MyHashMap {
    static class Entry {
        String word; //key
        MyLinkedList lineNumbers; //value

        Entry(String _word, int lineNumber) {
            word = _word;
            lineNumbers = new MyLinkedList(lineNumber);
        }

        //O(n) when n is the size of the lineNumbers List
        @Override
        public String toString() {
            String separator = " -> ";
            return word + separator + lineNumbers.toString(word.length() + separator.length()) + '\n';
        }
    }

    private final Entry[] array;

    public BONUS_MyHashMap(int size) {
        array = new Entry[size];
    }

    private boolean insert(String word, int lineNumber, int hash) {
        if (array[hash] == null) {
            array[hash] = new Entry(word, lineNumber);
            return true;
        } else if (array[hash].word.equalsIgnoreCase(word)) {
            array[hash].lineNumbers.insert(lineNumber);
            return true;
        }
        return false;
    }

    public void insert(String word, int lineNumber) {
        int hash = hash(word);
        boolean inserted = false;
        while (!inserted) {
            inserted = insert(word, lineNumber, hash);
            hash = (hash + 1) % array.length; //linear traversal
        }
    }

    public String search(String word) {
        int hash = hash(word);
        Entry entry = array[hash];
        int accesses = 0;
        while (accesses < array.length) {
            if (entry != null && entry.word.equalsIgnoreCase(word))
                break; // found word

            hash = (hash + 1) % array.length; //linear traversal
            entry = array[hash];
            accesses++;
        }
        return accesses < array.length ? entry.toString() : null;
    }

    private int hash(String word) {
        int hash = word.hashCode();
        return ((hash ^ hash >>> 16) & 0x7fffffff) % array.length;
    }

    public String getMostCommonWord() {
        Entry max = array[0];
        for (Entry entry : array) {
            if (entry != null && (max == null || entry.lineNumbers.size > max.lineNumbers.size))
                max = entry;
        }
        assert max != null;
        return max.toString();
    }

    public String toString() {
        Entry[] copy = new Entry[array.length];
        System.arraycopy(array, 0, copy, 0, array.length);

        Arrays.sort(copy, (a, b) -> {
            if (a == null && b == null) return 0;
            if (a == null) return 1;
            if (b == null) return -1;
            return a.word.compareTo(b.word);
        });

        StringBuilder sb = new StringBuilder();
        for (Entry entry : copy) {
            if (entry != null)
                sb.append(entry);
        }
        return sb.toString();

    }
}
