package Snippets;

import java.util.*;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.apache.commons.math3.primes.Primes.primeFactors;

//  54d496788776e49e6b00052f
public class SumOfFactorMultipliers {

    public static String sumOSumOfFactorMultipliers(int[] arr) {
        StringBuilder sb = new StringBuilder();
        TreeMap<Integer, Integer> treeMap = new TreeMap<>();
        for (int x : arr) {
            int ax = Math.abs(x);
            if (ax == 1) continue;
            new HashSet<>(primeFactors(ax)).forEach(f -> treeMap.merge(f, x, Integer::sum));
        }
        treeMap.forEach((key, value) -> sb.append("(").append(key).append(" ").append(value).append(")"));
        return sb.toString();
    }

}


class SoFM_TESTS {
    private static void test(int[] arr, String exp) {
        assertEquals(exp, SumOfFactorMultipliers.sumOSumOfFactorMultipliers(arr));
    }

    @Test
    public void doTests() {
        int[] lst = new int[]{12, 15};
        test(lst, "(2 12)(3 27)(5 15)");
        lst = new int[]{15, 21, 24, 30, 45};
        test(lst, "(2 54)(3 135)(5 90)(7 21)");
        lst = new int[]{107, 158, 204, 100, 118, 123, 126, 110, 116, 100};
        test(lst, "(2 1032)(3 453)(5 310)(7 126)(11 110)(17 204)(29 116)(41 123)(59 118)(79 158)(107 107)");
        lst = new int[]{-29804, -4209, -28265, -72769, -31744};
        test(lst, "(2 -61548)(3 -4209)(5 -28265)(23 -4209)(31 -31744)(53 -72769)(61 -4209)(1373 -72769)(5653 -28265)(7451 -29804)");
        lst = new int[]{17, -17, 51, -51};
        test(lst, "(3 0)(17 0)");
        lst = new int[]{173471};
        test(lst, "(41 173471)(4231 173471)");
        lst = new int[]{100000, 1000000};
        test(lst, "(2 1100000)(5 1100000)");
    }

}