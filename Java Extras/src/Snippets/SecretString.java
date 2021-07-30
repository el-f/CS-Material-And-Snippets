package Snippets;

import java.util.*;

public class SecretString {

    // my solution for this kata: https://www.codewars.com/kata/53f40dff5f9d31b813000774
    // (Recover a secret string from random triplets)

    public String recoverSecret(char[][] triplets) {
        return buildString(getOrderMap(triplets));
    }

    private String buildString(Map<Character, Set<Character>> map) {
        StringBuilder res = new StringBuilder();
        Character last;
        while (map.values().size() > 0) {
            for (Map.Entry<Character, Set<Character>> entry : map.entrySet()) {
                if (entry.getValue().isEmpty()) {
                    last = entry.getKey();
                    res.insert(0, last);
                    map.remove(last);
                    for (Set<Character> chars : map.values()) chars.remove(last);
                    break;
                }
            }
        }
        return res.toString();
    }

    private Map<Character, Set<Character>> getOrderMap(char[][] triplets) {
        Map<Character, Set<Character>> map = new HashMap<>();
        for (char[] triplet : triplets) {
            for (int i = 0; i < 3; i++) {
                if (!map.containsKey(triplet[i])) {
                    map.put(triplet[i], new HashSet<>());
                }
                if (i < 1) map.get(triplet[i]).add(triplet[2]);
                if (i < 2) map.get(triplet[i]).add(triplet[i + 1]);
            }
        }
        return map;
    }


    public static void main(String[] args) {
        char[][] triplets = {
                {'t', 'u', 'p'},
                {'w', 'h', 'i'},
                {'t', 's', 'u'},
                {'a', 't', 's'},
                {'h', 'a', 'p'},
                {'t', 'i', 's'},
                {'w', 'h', 's'}
        };
        System.out.println(
                "expected = 'whatisup', result = "
                        + new SecretString().recoverSecret(triplets)
        );
    }
}
