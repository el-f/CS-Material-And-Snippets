package Snippets;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class SubsetSumNegativeNumbers {
    static boolean isSubsetSumForAllNumbers(int[] set, int sum) {
        int bigNumber = (int) 1E6; // assume very big number -> at least as big as abs(min(set))
        List<Integer> transformedSet = Arrays.stream(set).map(x -> x + bigNumber).boxed().collect(Collectors.toList());
        int n = transformedSet.size();
        for (int i = 0; i < n; i++) {
            transformedSet.add(bigNumber);
        }
        return isSubsetSumForPositiveNumbers(
                transformedSet.stream().mapToInt(x -> x).toArray(),
                transformedSet.size(),
                n * bigNumber + sum);
    }

    // Returns true if there is a subset of
    // set[] with sum equal to given sum
    static boolean isSubsetSumForPositiveNumbers(int[] set, int n, int sum) {
        // The value of subset[i][j] will be
        // true if there is a subset of
        // set[0..j-1] with sum equal to i
        boolean[][] subset = new boolean[sum + 1][n + 1];

        // If sum is 0, then answer is true
        for (int i = 0; i <= n; i++)
            subset[0][i] = true;

        // If sum is not 0 and set is empty,
        // then answer is false
        for (int i = 1; i <= sum; i++)
            subset[i][0] = false;

        // Fill the subset table in bottom
        // up manner
        for (int i = 1; i <= sum; i++) {
            for (int j = 1; j <= n; j++) {
                subset[i][j] = subset[i][j - 1];
                if (i >= set[j - 1]) subset[i][j] = subset[i][j] || subset[i - set[j - 1]][j - 1];
            }
        }

        // uncomment this code to print table
//        for (int i = 0; i <= sum; i++) {
//            for (int j = 0; j <= n; j++)
//                System.out.println(subset[i][j]);
//        }

        return subset[sum][n];
    }

    public static void main(String[] args) {
        int[] A = { 9, -3, 0, 4, -5, -1 };
        int S = 7;
        if (isSubsetSumForAllNumbers(A, S))
            System.out.println("Found a subset with given sum");
        else
            System.out.println("No subset with given sum");

        int[] set = { 3, 34, 4, 12, 5, 2 };
        int sum = 9;
        if (isSubsetSumForAllNumbers(set, sum))
            System.out.println("Found a subset with given sum");
        else
            System.out.println("No subset with given sum");

    }
}
