package sorts;

/* Java program for Merge Sort */
public class MergeSort_TopDown {
    // Merges two subarrays of arr[].
    // First subarray is arr[start..mid]
    // Second subarray is arr[mid+1..end]
    void merge(int[] arr, int start, int mid, int end) {
        // Find sizes of two subarrays to be merged
        int n1 = mid - start + 1;
        int n2 = end - mid;

        /* Create temp arrays */
        int[] Left = new int[n1];
        int[] Right = new int[n2];

        /*Copy data to temp arrays*/
        if (n1 >= 0) System.arraycopy(arr, start, Left, 0, n1);
        for (int j = 0; j < n2; ++j)
            Right[j] = arr[mid + 1 + j];

        /* Merge the temp arrays */

        // Initial indexes of first and second subarrays
        int i = 0, j = 0;

        // Initial index of merged subarray array
        int k = start;
        while (i < n1 && j < n2) {
            if (Left[i] <= Right[j]) {
                arr[k] = Left[i];
                i++;
            } else {
                arr[k] = Right[j];
                j++;
            }
            k++;
        }

        /* Copy remaining elements of Left[] if any */
        while (i < n1) {
            arr[k] = Left[i];
            i++;
            k++;
        }

        /* Copy remaining elements of Right[] if any */
        while (j < n2) {
            arr[k] = Right[j];
            j++;
            k++;
        }
    }

    // Main function that sorts arr[start..end] using
    // merge()
    void mergeSort_TD(int[] arr, int start, int end) {
        if (start >= end) return;
        // Find the middle point
        int mid = (start + end) / 2;

        // Sort first and second halves
        mergeSort_TD(arr, start, mid);
        mergeSort_TD(arr, mid + 1, end);

        // Merge the sorted halves
        merge(arr, start, mid, end);
    }

    /* A utility function to print array of size n */
    static void printArray(int[] arr) {
        for (int j : arr) System.out.print(j + " ");
        System.out.println();
    }

    // Driver method
    public static void main(String[] args) {
        int[] arr = {12, 11, 13, 5, 6, 7};

        System.out.println("Given Array");
        printArray(arr);

        MergeSort_TopDown mergeSortTopDown = new MergeSort_TopDown();
        mergeSortTopDown.mergeSort_TD(arr, 0, arr.length - 1);

        System.out.println("\nSorted array");
        printArray(arr);
    }
}

