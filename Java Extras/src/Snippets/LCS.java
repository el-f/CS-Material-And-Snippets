package Snippets;

import lombok.Data;

import java.util.HashMap;
import java.util.Map;

/*
    Longest Common Sequence Solution
 */
public class LCS {

    @Data
    static class StringPair {
        final String first;
        final String second;
    }

    static Map<StringPair, String> cache = new HashMap<>();

    static String lcs(String a, String b) {
        if (a.length() == 0 || b.length() == 0) return "";

        StringPair current = new StringPair(a, b);
        if (cache.containsKey(current)) return cache.get(current);

        String result;
        if (a.charAt(a.length() - 1) == b.charAt(b.length() - 1)) {
            result = lcs(a.substring(0, a.length() - 1), b.substring(0, b.length() - 1)) + a.charAt(a.length() - 1);
        } else {
            String s1 = lcs(a.substring(0, a.length() - 1), b);
            String s2 = lcs(a, b.substring(0, b.length() - 1));
            result = s1.length() > s2.length() ? s1 : s2;
        }

        cache.put(current, result);
        return result;
    }

    // same but traversing the string forward in stead of backwards
    static String lcs2(String a, String b) {
        if (a.length() == 0 || b.length() == 0) return "";

        StringPair current = new StringPair(a, b);
        if (cache.containsKey(current)) return cache.get(current);

        String result;
        if (a.charAt(0) == b.charAt(0)) {
            result = a.charAt(0) + lcs2(a.substring(1), b.substring(1));
        } else {
            String s1 = lcs2(a.substring(1), b);
            String s2 = lcs2(a, b.substring(1));
            result = s1.length() > s2.length() ? s1 : s2;
        }

        cache.put(current, result);
        return result;
    }

    public static void main(String[] args) {
        System.out.println(lcs("nothardlythefinaltest", "zzzfinallyzzz").equals("final"));
        System.out.println(lcs("", "").equals(""));
        System.out.println(lcs2("nothardlythefinaltest", "zzzfinallyzzz").equals("final"));
        System.out.println(lcs2("", "").equals(""));
    }
}
