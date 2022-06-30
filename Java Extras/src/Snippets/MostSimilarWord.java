package Snippets;

import org.apache.commons.lang3.StringUtils;

import java.util.*;

class MostSimilarWord {

    private final String[] words;
    private final HashMap<String, Integer> cache = new HashMap<>();

    public MostSimilarWord(String[] words) { this.words = words; }

    int getLDist(String from, String to) {
        String key = from + "@" + to;
        if (!cache.containsKey(key)) cache.put(key, StringUtils.getLevenshteinDistance(from, to));
        return cache.get(key);
    }

    public String findMostSimilar(String to) {
        return Arrays.stream(words).reduce((s, s2) -> getLDist(s, to) < getLDist(s2, to) ? s : s2).orElse(null);
    }
}
