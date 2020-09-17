package structures.hash_tables;

// Java code illustrating clear() and clone() methods

import java.util.*;

//@SuppressWarnings("unchecked")
public class HashTableDemo {
    public static void main(String[] arg) {
        // creating a hash table
        Hashtable<Integer, String> h = new Hashtable<>();

        Hashtable<?, ?> h1;

        h.put(3, "Geeks");
        h.put(2, "forGeeks");
        h.put(1, "isBest");

        // create a clone or shallow copy of hash table h

        h1 = (Hashtable<?, ?>) h.clone();

        // checking clone h1
        System.out.println("values in clone: " + h1);

        // clear hash table h
        h.clear();

        // checking hash table h
        System.out.println("after clearing: " + h);
    }
}
