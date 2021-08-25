package Snippets;

import java.util.Arrays;
import java.util.HashMap;

// my solution for this kata: 52c31f8e6605bcc646000082
public class TwoSum {
    public static int[] twoSum(int[] numbers, int target) {
        HashMap<Integer, Integer> map = new HashMap<>();
        int remaining;
        for (int i = 0; i < numbers.length; i++) {
            remaining = target - numbers[i];
            if (map.containsKey(remaining)) {
                return new int[]{map.get(remaining), i};
            }
            map.putIfAbsent(numbers[i], i);
        }
        return null;
    }


    public static void main(String[] args) {
        System.out.println((Arrays.toString(twoSum(new int[]{1, 2, 3, 5, 9, 8, 5, 4, 11, 13}, 17))));
    }
}