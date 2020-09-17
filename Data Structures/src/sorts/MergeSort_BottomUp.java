package sorts;

import java.util.Arrays;

public class MergeSort_BottomUp {

    public static void main(String[] args) {
        int[] x = {6, 3, 7, 2, 8, 4, 9, 1};
        int[] help = new int[x.length];

        System.out.println("Before sort:  " + Arrays.toString(x));

        mergeSort_BU(x, help);  // Merge sort

        System.out.println("\nAfter sort:   " + Arrays.toString(x));
    }

    public static void merge(int[] a,
                             int iLeft, int iMiddle, int iRight,
                             int[] tmp) {
        int i, j, k;

        i = iLeft;
        j = iMiddle;
        k = iLeft;

        while (i < iMiddle || j < iRight) {
            if (i < iMiddle && j < iRight) {  // Both array have elements
                if (a[i] < a[j])
                    tmp[k++] = a[i++];
                else
                    tmp[k++] = a[j++];
            } else if (i == iMiddle)
                tmp[k++] = a[j++];     // a is empty
            else if (j == iRight)
                tmp[k++] = a[i++];     // b is empty
        }
    }

    public static void mergeSort_BU(int[] a, int[] tmp) {
        int width;

        for (width = 1; width < a.length; width = 2 * width) {
            // Combine sections of array a of width "width"
            int i;

            for (i = 0; i < a.length; i = i + 2 * width) {
                int left, middle, right;

                left = i;
                middle = i + width;
                right = i + 2 * width;

                merge(a, left, middle, right, tmp);

            }

         /* ================================================
	    Copy tmp[ ] back to a[ ] for next iteration
	    ================================================ */
            for (i = 0; i < a.length; i++)
                a[i] = tmp[i];

            System.out.println("After 1 iter: " + Arrays.toString(a));
        }
    }
}