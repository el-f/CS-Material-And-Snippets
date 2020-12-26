package sorts;

public class SelectionSort {
    void selectSort(int[] arr) {
        int n = arr.length;

        // One by one move boundary of unsorted subarray
        for (int i = 0; i < n - 1; i++) {
            // Find the minimum element in unsorted array
            int min_idx = i;
            for (int j = i + 1; j < n; j++)
                if (arr[j] < arr[min_idx])
                    min_idx = j;

            // Swap the found minimum element with the first
            // element
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }

    // Prints the array
    void printArray(int[] arr) {
        for (int j : arr) System.out.print(j + " ");
        System.out.println();
    }

    // Driver code to test above
    public static void main(String[] args) {
        SelectionSort ss = new SelectionSort();
        int[] arr = {64, 25, 12, 22, 11};
        ss.selectSort(arr);
        System.out.println("Sorted array");
        ss.printArray(arr);
    }
}
