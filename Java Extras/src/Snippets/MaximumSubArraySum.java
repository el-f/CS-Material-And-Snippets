package Snippets;


public class MaximumSubArraySum {

    public static int maxSubArraySum(int[] arr) {
        int totalMax = 0;
        int currentMax = 0;

        for (int x : arr) {
            if (x > 0 && currentMax <= 0) currentMax = x;
            else currentMax += x;
            if (currentMax > totalMax) totalMax = currentMax;
        }

        return totalMax;
    }


    public static void main(String[] args) {
        System.out.println(
                maxSubArraySum(new int[]{-2, 1, -3, 4, -1, 2, 1, -5, 4})
                        == 6
        );

        System.out.println(
                maxSubArraySum(new int[]{7, 4, 11, -11, 39, 36, 10, -6, 37, -10, -32, 44, -26, -34, 43, 43})
                        == 155
        );

        System.out.println(
                maxSubArraySum(new int[]{-2, -1, -3, -4, -1, -2, -1, -5, -4})
                        == 0
        );
    }

}
