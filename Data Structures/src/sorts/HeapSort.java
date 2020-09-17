package sorts;

import structures.heaps.MaxHeap;

import java.util.Arrays;

public class HeapSort {
    public static void main(String[] args) {
        int[] array = new int[0];
        heapSort(array);
        System.out.println(Arrays.toString(array));
    }

    public static void heapSort(int[] array){
        MaxHeap.buildHeap(array);
        while (array[0] > 1) {
            array[array[0]] = array[1];
            array[0]--;
            MaxHeap.siftDown_v2(array, 1);
        }
    }
}
