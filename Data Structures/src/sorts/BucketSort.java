package sorts;

// Java program to sort an array
// using bucket sort

import java.util.ArrayList;
import java.util.Collections;

class BucketSort {

    // Function to sort arr[] of size n
// using bucket sort
    static void bucketSort(float[] arr, int n) {
        if (n <= 0) return;

        // 1) Create n empty buckets
        @SuppressWarnings("unchecked")
        ArrayList<Float>[] b = new ArrayList[n];

        for (int i = 0; i < n; i++) {
            b[i] = new ArrayList<>();
        }

        // 2) Put array elements in different buckets
        for (int i = 0; i < n; i++) {
            int idx = (int) arr[i] * n;
            b[idx].add(arr[i]);
        }

        // 3) Sort individual buckets
        for (int i = 0; i < n; i++) {
            Collections.sort(b[i]);
        }

        // 4) Concatenate all buckets into arr[]
        int index = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < b[i].size(); j++) {
                arr[index++] = b[i].get(j);
            }
        }
    }

    // Driver code
    public static void main(String[] args) {
        float[] arr = {(float) 0.897, (float) 0.565,
                (float) 0.656, (float) 0.1234,
                (float) 0.665, (float) 0.3434};

        int n = arr.length;
        bucketSort(arr, n);

        System.out.println("Sorted array is ");
        for (float el : arr) {
            System.out.print(el + " ");
        }
    }
}