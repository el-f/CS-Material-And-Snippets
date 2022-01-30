package Snippets;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.stream.Collectors;

public class Counter<T> {

    private final Map<T, Integer> counts;

    public Counter() {
        counts = new ConcurrentHashMap<>();
    }

    public Counter(Iterable<T> iterable) {
        this();
        for (T item : iterable) { add(item); }
    }

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
        @SuppressWarnings("all")
        SortedSet<Map.Entry<K, V>> sortedEntries = new TreeSet<>(
                Map.Entry.<K, V> comparingByValue()
                        .reversed()
                        .thenComparing((e1, e2) -> {
                            K key1 = e1.getKey(), key2 = e2.getKey();
                            if (key1 instanceof Comparable && key2 instanceof Comparable) {
                                return ((Comparable) key1).compareTo((Comparable) key2);
                            }
                            return 0;
                        })
                        .thenComparing(entry -> entry.getKey().getClass().hashCode())
        );
        sortedEntries.addAll(map.entrySet());
        return sortedEntries;
    }

    public Map<T, Integer> getUnderlyingMap() {
        return counts;
    }

    @Override
    public String toString() {
        return getOrderedEntries().toString();
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
        System.out.println(counter.getUnderlyingMap());

        List<String> list = Arrays.asList("1", "abc", "a", "b", "c", "c", "1", "2", "3", "1", "2");
        System.out.println(new Counter<>(list));

    }
}