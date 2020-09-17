package sorts;

// Java program for implementation of QuickSort
@SuppressWarnings({"unused", "RedundantSuppression"})
public class QuickSort {


    /* This function takes last element as pivot,
    places the pivot element at its correct
    position in sorted array, and places all
    smaller (smaller than pivot) to left of
    pivot and all greater elements to right
    of pivot */
    //(Lomuto's approach)
    int lastElementPartition(int[] arr, int start, int end) {
        int pivot = arr[end];
        int i = start - 1; // index of smaller element
        for (int j = start; j < end; j++) {
            // If current element is smaller than the pivot
            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, end);

        return i + 1;
    }

    //first element as pivot (Hoare's approach)
    @SuppressWarnings({"unused", "RedundantSuppression"})
    int firstElementPartition(int[] arr, int start, int end) {
        int pivot = arr[start];
        int i = start + 1;
        int j = end;
        while (i < j) {
            while (i <= end && arr[i] < pivot) i++;
            while (j > start && arr[j] > pivot) j--;
            if (i < j) swap(arr, i, j);
        }
        swap(arr, start, i - 1);
        return i - 1;
    }

    int improvedPartition(int[] arr, int start, int end) {
        swap(arr, end, medianOfThreeIndex(arr, start, (start + end) / 2, end));
        return lastElementPartition(arr, start, end);
    }


    //Basically XOR
    int medianOfThree(int x, int y, int z) {
        if (x > y != x > z) return x;
        if (y > x != y > z) return y;
        return z;
    }

    //Basically XOR
    int medianOfThreeIndex(int[] arr, int x, int y, int z) {
        if (arr[x] > arr[y] != arr[x] > arr[z]) return x;
        if (arr[y] > arr[x] != arr[y] > arr[z]) return y;
        return z;
    }

    void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }


    /* The main function that implements QuickSort()
    arr[] --> Array to be sorted,
    start --> Starting index,
    end --> Ending index */
    void quickSort(int[] arr, int start, int end) {
        if (start >= end) return;
			/* pi is partitioning index, arr[pi] is
			now at right place */
        int pi = lastElementPartition(arr, start, end);

        // Recursively sort elements before
        // partition and after partition
        quickSort(arr, start, pi - 1);
        quickSort(arr, pi + 1, end);

    }

    //O(nlgn) + O(20n)
    void improvedQuickSort(int[] arr) {
        improvedQuickSort(arr, 0, arr.length - 1);
        InsertionSort.insertionSort(arr);
    }


    void improvedQuickSort(int[] arr, int start, int end) {
        if (end - start < 20) return;
        int pi = improvedPartition(arr, start, end);
        improvedQuickSort(arr, start, pi - 1);
        improvedQuickSort(arr, pi + 1, end);
    }


    /* A utility function to print array of size n */
    static void printArray(int[] arr) {
        for (int j : arr) System.out.print(j + " ");
        System.out.println();
    }

    // Driver program
    public static void main(String[] args) {
        int[] arr = {10, 7, 8, 9, 1, 5};
        int n = arr.length;
        QuickSort qs = new QuickSort();
        qs.improvedQuickSort(arr);
//        qs.quickSort(arr, 0, n - 1);

        System.out.println("sorted array");
        printArray(arr);
    }


}

