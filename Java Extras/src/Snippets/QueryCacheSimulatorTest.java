package Snippets;

import lombok.AllArgsConstructor;
import lombok.Data;
import org.junit.*;
import org.junit.runners.MethodSorters;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.IntStream;

import static Snippets.QueryCacheSimulator.*;
import static Snippets.QueryCacheSimulator.getNumbers;

/**
 * Simulating caching results from an external API, and using them to reduce the number of calls to the API.
 * The API is called with a range to get results for, and the API returns a list of results for that range.
 */
class QueryCacheSimulator {

    @Data
    @AllArgsConstructor
    public static class EntityCache {
        int offset;
        int number;

        public String toString() {
            return "(offset: " + offset + ", number: " + number + " [covers " + offset + "-" + (offset + number - 1) + "])";
        }
    }

    public static void main(String[] args) {
        List<EntityCache> caches = new ArrayList<>();
        caches.add(new EntityCache(10, 10));
        caches.add(new EntityCache(30, 10));

        List<Integer> numbers = getNumbers(caches, 5, 55);
        System.out.println("Numbers: " + numbers);
    }


    public static List<Integer> getNumbers(List<EntityCache> caches, int offset, int number) {
        List<Integer> recipes = new ArrayList<>();
        int neededStart = offset;
        int neededEnd = offset + number;
        int currentOffset = offset;
        List<EntityCache> newCaches = new ArrayList<>();

        for (EntityCache cache : caches) {
            int cacheStart = cache.offset;
            int cacheEnd = cache.offset + cache.number;

            if (cacheEnd < neededStart) {
                continue;
            }

            if (cacheStart >= neededEnd) {
                break;
            }

            if (currentOffset < cacheStart) {
                System.out.println("Query API for range " + currentOffset + "-" + (cacheStart - 1));
                for (int i = currentOffset; i < cacheStart; i++) {
                    recipes.add(i);
                }

                newCaches.add(new EntityCache(currentOffset, cacheStart - currentOffset));

                currentOffset = cacheStart;
            }

            int start = Math.max(currentOffset - cacheStart, 0);
            int end = Math.min(neededEnd - cacheStart, cache.number);
            System.out.println("Get from DB for range " + (cacheStart + start) + "-" + (cacheStart + end - 1));
            for (int i = start; i < end; i++) {
                recipes.add(cacheStart + i);
            }

            currentOffset = cacheEnd;
        }

        if (currentOffset < neededEnd) {
            System.out.println("Query API for range " + currentOffset + "-" + (neededEnd - 1));
            for (int i = currentOffset; i < neededEnd; i++) {
                recipes.add(i);
            }

            newCaches.add(new EntityCache(currentOffset, neededEnd - currentOffset));

        }

        System.out.println("newCaches: " + newCaches);
        List<EntityCache> mergedCaches = mergeCaches(caches, newCaches);
        System.out.println("mergedCaches: " + mergedCaches);

        return recipes;
    }

    public static List<EntityCache> mergeCaches(List<EntityCache> existingCaches, List<EntityCache> newCaches) {
        if (existingCaches.isEmpty()) {
            return newCaches;
        }

        if (newCaches.isEmpty()) {
            return existingCaches;
        }

        List<EntityCache> allCaches = new ArrayList<>(existingCaches);
        allCaches.addAll(newCaches);

        // Sort allCaches by the offset
        allCaches.sort(Comparator.comparingInt(EntityCache::getOffset));

        List<EntityCache> mergedCaches = new ArrayList<>();
        EntityCache currentCache = allCaches.get(0);

        for (int i = 1; i < allCaches.size(); i++) {
            EntityCache nextCache = allCaches.get(i);

            // If the current cache overlaps with the next cache, merge them
            if (currentCache.getOffset() + currentCache.getNumber() >= nextCache.getOffset()) {
                currentCache = new EntityCache(currentCache.getOffset(),
                                               Math.max(currentCache.getOffset() + currentCache.getNumber(),
                                                        nextCache.getOffset() + nextCache.getNumber()) - currentCache.getOffset());
            } else {
                // Otherwise, add the current cache to the mergedCaches list and move on to the next cache
                mergedCaches.add(currentCache);
                currentCache = nextCache;
            }
        }
        mergedCaches.add(currentCache);

        return mergedCaches;
    }

}

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class QueryCacheSimulatorTest {

    public void testGetNumbers(int offset, int number, List<EntityCache> caches) {
        System.out.println("Query for range " + offset + "-" + (offset + number - 1) + " (inclusive)");
        System.out.println("caches: " + caches.toString());
        List<Integer> expected = IntStream.range(offset, offset + number).collect(ArrayList::new, ArrayList::add, ArrayList::addAll);
        List<Integer> actual = getNumbers(caches, offset, number);

        Assert.assertEquals(expected, actual);
    }

    @Before
    public void before() {
        System.out.println("--------------------");
    }

    @Test
    public void _0_shouldHandleEmptyCaches() {
        List<EntityCache> caches = new ArrayList<>();
        testGetNumbers(5, 55, caches);
    }

    @Test
    public void _1_shouldGetRangeWhichCoversAllCaches() {
        List<EntityCache> caches = new ArrayList<>();
        caches.add(new EntityCache(10, 10));
        caches.add(new EntityCache(30, 10));
        testGetNumbers(5, 55, caches);
    }

    @Test
    public void _2_shouldGetRangeWhichIsIncludedInOneCache() {
        List<EntityCache> caches = new ArrayList<>();
        caches.add(new EntityCache(10, 10));
        caches.add(new EntityCache(30, 10));
        testGetNumbers(15, 5, caches);
    }

    @Test
    public void _3_shouldGetRangeWhichIsIncludedInTwoCaches() {
        List<EntityCache> caches = new ArrayList<>();
        caches.add(new EntityCache(10, 10));
        caches.add(new EntityCache(30, 10));
        testGetNumbers(15, 15, caches);
    }

    @Test
    public void _4_shouldGetRangeWhichIsNotIncludedInAnyCache() {
        List<EntityCache> caches = new ArrayList<>();
        caches.add(new EntityCache(10, 10));
        caches.add(new EntityCache(30, 10));
        testGetNumbers(5, 5, caches);
    }

    @Test
    public void _5_shouldGetRangeWhichIsExactlyTheSameAsOneCache() {
        List<EntityCache> caches = new ArrayList<>();
        caches.add(new EntityCache(10, 10));
        caches.add(new EntityCache(30, 10));
        testGetNumbers(10, 10, caches);
    }

    @Test
    public void _6_shouldGetRangeWhichOverlapsOneCache() {
        List<EntityCache> caches = new ArrayList<>();
        caches.add(new EntityCache(10, 10));
        caches.add(new EntityCache(30, 10));
        testGetNumbers(5, 15, caches);
    }

    public void testMergeCaches(List<EntityCache> existingCaches, List<EntityCache> newCaches, List<EntityCache> expected) {
        System.out.println("existingCaches: " + existingCaches.toString());
        System.out.println("newCaches: " + newCaches.toString());
        System.out.println("expected: " + expected.toString());
        List<EntityCache> actual = mergeCaches(existingCaches, newCaches);
        Assert.assertEquals(expected, actual);
    }

    @Test
    public void _7_shouldMergeCachesFillHole() {
        List<EntityCache> existingCaches = new ArrayList<>();
        existingCaches.add(new EntityCache(10, 10));
        existingCaches.add(new EntityCache(30, 10));

        List<EntityCache> newCaches = new ArrayList<>();
        newCaches.add(new EntityCache(20, 10));

        List<EntityCache> expected = new ArrayList<>();
        expected.add(new EntityCache(10, 30));

        testMergeCaches(existingCaches, newCaches, expected);
    }

    @Test
    public void _8_shouldMergeCachesWithHoleRemaining() {
        List<EntityCache> existingCaches = new ArrayList<>();
        existingCaches.add(new EntityCache(10, 10));
        existingCaches.add(new EntityCache(30, 10));

        List<EntityCache> newCaches = new ArrayList<>();
        newCaches.add(new EntityCache(25, 10));

        List<EntityCache> expected = new ArrayList<>();
        expected.add(new EntityCache(10, 10));
        expected.add(new EntityCache(25, 15));

        testMergeCaches(existingCaches, newCaches, expected);
    }

    @Test
    public void _9_shouldNotMergeCachesWithNoOverlap() {
        List<EntityCache> existingCaches = new ArrayList<>();
        existingCaches.add(new EntityCache(0, 1));
        existingCaches.add(new EntityCache(3, 1));

        List<EntityCache> newCaches = new ArrayList<>();
        newCaches.add(new EntityCache(5, 1));

        List<EntityCache> expected = new ArrayList<>();
        expected.add(new EntityCache(0, 1));
        expected.add(new EntityCache(3, 1));
        expected.add(new EntityCache(5, 1));

        testMergeCaches(existingCaches, newCaches, expected);
    }

    @Test
    public void _10_shouldMergeCachesWithOverlap() {
        List<EntityCache> existingCaches = new ArrayList<>();
        existingCaches.add(new EntityCache(0, 2));
        existingCaches.add(new EntityCache(3, 1));

        List<EntityCache> newCaches = new ArrayList<>();
        newCaches.add(new EntityCache(2, 1));

        List<EntityCache> expected = new ArrayList<>();
        expected.add(new EntityCache(0, 4));

        testMergeCaches(existingCaches, newCaches, expected);
    }

    @Test
    public void _11_shouldMergeCachesWithOverlap() {
        List<EntityCache> existingCaches = new ArrayList<>();
        existingCaches.add(new EntityCache(0, 1));
        existingCaches.add(new EntityCache(3, 1));

        List<EntityCache> newCaches = new ArrayList<>();
        newCaches.add(new EntityCache(1, 1));

        List<EntityCache> expected = new ArrayList<>();
        expected.add(new EntityCache(0, 2));
        expected.add(new EntityCache(3, 1));

        testMergeCaches(existingCaches, newCaches, expected);
    }

    @Test
    public void _12_shouldHandleMergingBigNumbers() {
        List<EntityCache> existingCaches = new ArrayList<>();
        existingCaches.add(new EntityCache(0, 1000000000));
        existingCaches.add(new EntityCache(2000000000, 1000000000));

        List<EntityCache> newCaches = new ArrayList<>();
        newCaches.add(new EntityCache(1000000000, 1000000000));

        List<EntityCache> expected = new ArrayList<>();
        expected.add(new EntityCache(0, 2000000000));

        testMergeCaches(existingCaches, newCaches, expected);
    }

    @Test
    public void _13_shouldHandleMergingBigNumbersWithHolesRemaining() {
        List<EntityCache> existingCaches = new ArrayList<>();
        existingCaches.add(new EntityCache(0, 100000000));
        existingCaches.add(new EntityCache(200000000, 100000000));

        List<EntityCache> newCaches = new ArrayList<>();
        newCaches.add(new EntityCache(150000000, 100000000));

        List<EntityCache> expected = new ArrayList<>();
        expected.add(new EntityCache(0, 100000000));
        expected.add(new EntityCache(150000000, 150000000));

        testMergeCaches(existingCaches, newCaches, expected);
    }

    @Test
    public void shouldHandleMergingEmptyCaches() {
        List<EntityCache> existingCaches = new ArrayList<>();
        List<EntityCache> newCaches = new ArrayList<>();
        List<EntityCache> expected = new ArrayList<>();
        testMergeCaches(existingCaches, newCaches, expected);
    }
}
