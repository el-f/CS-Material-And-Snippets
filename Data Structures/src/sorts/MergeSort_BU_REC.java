package sorts;

public class MergeSort_BU_REC {
    public static void mergeSort(int[] array) {
        if (array == null) return;

        if (array.length > 1) {
            int mid = array.length / 2;

            int[] left = new int[mid];
            System.arraycopy(array, 0, left, 0, mid);

            int[] right = new int[array.length - mid];
            System.arraycopy(array, mid, right, 0, array.length - mid);
            mergeSort(left);
            mergeSort(right);

            int i = 0;
            int j = 0;
            int k = 0;

            while (i < left.length && j < right.length) {
                if (left[i] < right[j]) {
                    array[k] = left[i];
                    i++;
                } else {
                    array[k] = right[j];
                    j++;
                }
                k++;
            }
            while (i < left.length) {
                array[k] = left[i];
                i++;
                k++;
            }
            while (j < right.length) {
                array[k] = right[j];
                j++;
                k++;
            }
        }
    }

    public static void main(String[] args) {
        int[] arr = {12, 11, 13, 5, 6, 7};
//        int[] x = {6, 3, 7, 2, 8, 4, 9, 1};
        System.out.println("Given array is");

        for (int k : arr) System.out.print(k + " ");

        mergeSort(arr);

        System.out.println("\n");
        System.out.println("Sorted array is");

        for (int j : arr) System.out.print(j + " ");
    }
}
