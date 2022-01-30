package Snippets;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;
import java.util.stream.Collectors;

public class Counter<T> {

    private final ConcurrentMap<T, Integer> counts = new ConcurrentHashMap<>();

    public void add(T it) {
        counts.merge(it, 1, Integer::sum);
    }

    public Integer count(T it) {
        return counts.get(it);
    }

    public T mostCommonItem() {
        return mostCommon(1).get(0);
    }

    public List<T> mostCommon() {
        return mostCommon(counts.size());
    }

    public List<T> mostCommon(int n) {
        return counts.entrySet().stream()
                .sorted((e1, e2) -> Integer.compare(e2.getValue(), e1.getValue()))
                .limit(n)
                .map(Map.Entry::getKey)
                .collect(Collectors.toList());
    }

    public SortedSet<Map.Entry<T, Integer>> getOrderedEntries() {
        return entriesSortedByValues(counts);
    }

    private <K, V extends Comparable<? super V>> SortedSet<Map.Entry<K, V>> entriesSortedByValues(Map<K, V> map) {
        SortedSet<Map.Entry<K, V>> sortedEntries = new TreeSet<>(
                Map.Entry.<K, V> comparingByValue()
                        .reversed()
                        .thenComparing(entry -> entry.getKey().getClass().hashCode())
        );
        sortedEntries.addAll(map.entrySet());
        return sortedEntries;
    }
}

class CounterExample {
    public static void main(String[] args) {
        Counter<Object> counter = new Counter<>();
        counter.add(1);
        counter.add(1);
        counter.add(1);
        counter.add("wow");
        counter.add("wow");
        counter.add(Collections.emptyList());
        counter.add(Collections.emptyList());
        counter.add(Collections.emptyMap());

        System.out.println(counter.mostCommon());
        System.out.println(counter.mostCommonItem());
        System.out.println(counter.mostCommon(2));
        System.out.println(counter.count(1));
        System.out.println(counter.getOrderedEntries());
    }
}