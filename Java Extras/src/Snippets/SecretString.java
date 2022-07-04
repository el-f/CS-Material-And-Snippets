package Snippets;

import java.util.*;

public class SecretString {

    //  53f40dff5f9d31b813000774

    public String recoverSecret(char[][] triplets) {
        return buildString(getOrderMap(triplets));
    }

    // find last character one at a time and build string from end to start
    private String buildString(Map<Character, Set<Character>> map) {
        StringBuilder res = new StringBuilder();
        Character last;
        while (!map.isEmpty()) {
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

    // map each char to all chars that come after it
    private Map<Character, Set<Character>> getOrderMap(char[][] triplets) {
        Map<Character, Set<Character>> map = new HashMap<>();
        for (char[] triplet : triplets) {
            for (int i = 0; i < 3; i++) {
                map.putIfAbsent(triplet[i], new HashSet<>());
                for (int j = 1; j + i <= 2; j++)
                    map.get(triplet[i]).add(triplet[i + j]);
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
