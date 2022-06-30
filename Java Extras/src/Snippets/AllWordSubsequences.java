package Snippets;

import org.apache.commons.lang3.StringUtils;

import java.util.*;


public class AllWordSubsequences {

    public static final String WORD_TO_FIND = "banana";

    static Set<String> recursive(Set<String> set, String word, int wordIndex, int bananasIndex) {
        if (bananasIndex >= WORD_TO_FIND.length()) {
            set.add(word.substring(0, wordIndex) + StringUtils.repeat('-',word.length() - wordIndex));
            return set;
        }
        if (wordIndex >= word.length()) return set;
        if (word.charAt(wordIndex) == WORD_TO_FIND.charAt(bananasIndex)) {
            recursive(set, word, wordIndex + 1, bananasIndex + 1);
        }
        return recursive(set, word.substring(0, wordIndex) + "-" + word.substring(wordIndex + 1), wordIndex + 1, bananasIndex);
    }

    static Set<String> allWordsSubsequences(final String s) { return recursive(new HashSet<>(), s, 0, 0); }
}

class AWSS_Test {


    public static void main(String[] args) {
        doTest("banann", new String[]{});
        doTest("banana", new String[]{ "banana" });
        doTest("bbananana", new String[]{ "b-an--ana", "-banana--", "-b--anana", "b-a--nana", "-banan--a",
                "b-ana--na", "b---anana", "-bana--na", "-ba--nana", "b-anan--a",
                "-ban--ana", "b-anana--" });
        doTest("bananaaa", new String[]{ "banan-a-", "banana--", "banan--a" });
        doTest("bananana", new String[]{ "ban--ana", "ba--nana", "bana--na", "b--anana", "banana--", "banan--a" });

    }

    private static void doTest(String word, String[] expectedArr) {
        Set<String> expected = new HashSet<>(Arrays.asList(expectedArr));
        Set<String> actual = AllWordSubsequences.allWordsSubsequences(word);
        System.out.print("Testing " + word + ": ");
        if (actual.equals(expected)) {
            System.out.println("OK");
        } else {
            System.out.println("FAIL");
            System.out.println("Expected: " + expected);
            System.out.println("Actual:   " + actual);
        }
    }
}