package Snippets;

import java.util.*;
import java.util.stream.Collectors;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

// my solution for this kata: 5279f6fe5ab7f447890006a7
public class LocalMaximums {

    static final String POS = "pos", PEAKS = "peaks";

    static int getNext(int[] arr, int index, int[] skipIndex) {
        int it = arr[index++];
        while (index < arr.length && arr[index] == it) {
            skipIndex[0] = index++;
        }
        return index >= arr.length ? Integer.MAX_VALUE : arr[index];
    }

    public static Map<String, List<Integer>> localMaximums(int[] arr) {
        Map<String, List<Integer>> result = new LinkedHashMap<>();
        int[] skipIndex = new int[1];
        int si;
        result.put(POS, new ArrayList<>());
        result.put(PEAKS, new ArrayList<>());
        for (int i = 1; i < arr.length - 1; i++) {
            if (i <= (si = skipIndex[0])) {
                if (i < si) i = si;
                continue;
            }
            if (arr[i - 1] < arr[i] && arr[i] > getNext(arr, i, skipIndex)) {
                result.get(POS).add(i);
                result.get(PEAKS).add(arr[i]);
            }
        }
        return result;
    }
}

class LM_TESTS {

    private static final String[] MSGS = {
            "should support finding peaks",
            "should support finding peaks, but should ignore peaks on the edge of the array",
            "should support finding peaks; if the peak is a plateau, it should only return the position of the first element of the plateau",
            "should support finding peaks; if the peak is a plateau, it should only return the position of the first element of the plateau",
            "should support finding peaks, but should ignore peaks on the edge of the array",
            "should support finding peaks, but should ignore peaks on the edge of the array",
            "should support finding peaks, despite the plateau",
            "should support finding peaks",
            "should return an object with empty arrays if the input is an empty array",
            "should return an object with empty arrays if the input does not contain any peak"
    };

    private static final int[][] TEST_CASES = {
            {1, 2, 3, 6, 4, 1, 2, 3, 2, 1},
            {3, 2, 3, 6, 4, 1, 2, 3, 2, 1, 2, 3},
            {3, 2, 3, 6, 4, 1, 2, 3, 2, 1, 2, 2, 2, 1},
            {2, 1, 3, 1, 2, 2, 2, 2, 1},
            {2, 1, 3, 1, 2, 2, 2, 2},
            {2, 1, 3, 2, 2, 2, 2, 5, 6},
            {2, 1, 3, 2, 2, 2, 2, 1},
            {1, 2, 5, 4, 3, 2, 3, 6, 4, 1, 2, 3, 3, 4, 5, 3, 2, 1, 2, 3, 5, 5, 4, 3},
            {},
            {1, 1, 1, 1}
    };

    private static final int[][] EXPECTED_POS = {
            {3, 7},
            {3, 7},
            {3, 7, 10},
            {2, 4},
            {2},
            {2},
            {2},
            {2, 7, 14, 20},
            {},
            {}
    };

    private static final int[][] EXPECTED_PEAKS = {
            {6, 3},
            {6, 3},
            {6, 3, 2},
            {3, 2},
            {3},
            {3},
            {3},
            {5, 6, 5, 5},
            {},
            {}
    };


    @Test
    public void fixedTests() {
        for (int n = 0; n < TEST_CASES.length; n++) {
            final int[] p1 = EXPECTED_POS[n], p2 = EXPECTED_PEAKS[n];
            Map<String, List<Integer>> expected = new HashMap<String, List<Integer>>() {{
                put("pos", Arrays.stream(p1).boxed().collect(Collectors.toList()));
                put("peaks", Arrays.stream(p2).boxed().collect(Collectors.toList()));
            }};
            Map<String, List<Integer>> actual = LocalMaximums.localMaximums(TEST_CASES[n]);
            assertEquals(expected, actual, MSGS[n]);
        }
    }
}
