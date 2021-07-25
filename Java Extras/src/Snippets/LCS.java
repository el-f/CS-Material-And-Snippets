package Snippets;

import lombok.Data;

import java.util.HashMap;
import java.util.Map;

public class LCS {

    @Data
    static class StringPair {
        final String first;
        final String second;
    }

    static Map<StringPair, String> cache = new HashMap<>();

    static String lcs(String a, String b) {
        if (a.length() == 0 || b.length() == 0) return "";

        if (cache.containsKey(new StringPair(a, b))) return cache.get(new StringPair(a, b));

        String result;
        if (a.charAt(a.length() - 1) == b.charAt(b.length() - 1)) {
            result = lcs(a.substring(0, a.length() - 1), b.substring(0, b.length() - 1)) + a.charAt(a.length() - 1);
        } else {
            String s1 = lcs(a.substring(0, a.length() - 1), b);
            String s2 = lcs(a, b.substring(0, b.length() - 1));
            result = s1.length() > s2.length() ? s1 : s2;
        }

        cache.put(new StringPair(a, b), result);
        return result;
    }

    public static void main(String[] args) {
        System.out.println(lcs("nothardlythefinaltest", "zzzfinallyzzz").equals("final"));
        System.out.println(lcs("", "").equals(""));
    }
}
