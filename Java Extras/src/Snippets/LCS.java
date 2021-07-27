package Snippets;

import lombok.Data;
import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.Map;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.assertTrue;

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

    @Test
    static void doTestsLCS1() {
        assertTrue(Stream.of(
                (""         .equals(lcs("", ""))),
                ("final"    .equals(lcs("nothardlythefinaltest", "zzzfinallyzzz"))),
                ("abc"      .equals(lcs("abcdef", "abc"))),
                ("acf"      .equals(lcs("abcdef", "acf"))),
                ("nottest"  .equals(lcs("anothertest", "notatest"))),
                ("12356"    .equals(lcs("132535365", "123456789")))
        ).allMatch(it -> it));

        cache.clear();
    }

    @Test
    static void doTestsLCS2() {
        assertTrue(Stream.of(
                (""         .equals(lcs2("", ""))),
                ("final"    .equals(lcs2("nothardlythefinaltest", "zzzfinallyzzz"))),
                ("abc"      .equals(lcs2("abcdef", "abc"))),
                ("acf"      .equals(lcs2("abcdef", "acf"))),
                ("nottest"  .equals(lcs2("anothertest", "notatest"))),
                ("12356"    .equals(lcs2("132535365", "123456789")))
        ).allMatch(it -> it));

        cache.clear();
    }

    public static void main(String[] args) {
        doTestsLCS1();
        doTestsLCS2();
    }
}
