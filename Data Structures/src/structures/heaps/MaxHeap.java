package structures.heaps;

import java.util.Arrays;

// Java program to implement Max Heap
@SuppressWarnings({"unused", "RedundantSuppression"})
public class MaxHeap {
    public static final boolean print = false;


    public static void main(String[] arg) {
//        System.out.println("The Max Heap is ");
//        MaxHeap maxHeap = new MaxHeap(15);
//        maxHeap.insert(5);
//        maxHeap.insert(3);
//        maxHeap.insert(17);
//        maxHeap.insert(10);
//        maxHeap.insert(84);
//        maxHeap.insert(19);
//        maxHeap.insert(6);
//        maxHeap.insert(22);
//        maxHeap.insert(9);
//        maxHeap.print();
//        System.out.println(Arrays.toString(maxHeap.heap));
//        maxHeap.removeMax();
//        System.out.println(Arrays.toString(maxHeap.heap));
//        System.out.println("The max val is " + maxHeap.extractMax());
        int[] array = {10, 9, 1, 9, 5, 18, 16, 13, 19, 14, 12};
        buildHeap(array);
        System.out.println(Arrays.toString(array));
    }


    private final int[] heap;

    // Constructor to initialize an
    // empty max heap with given maximum
    // capacity.
    public MaxHeap(int size) {
        heap = new int[size + 1];
        heap[0] = 0; //will utilize size pointer
    }

    // Returns position of parent
    private static int parent(int pos) {
        return pos / 2;
    }

    // Below two functions return left and
    // right children.
    private static int left(int pos) {
        return 2 * pos;
    }

    private static int right(int pos) {
        return 2 * pos + 1;
    }

    // Returns true of given node is leaf
    private boolean isLeaf(int pos) {
        return pos >= heap[0] / 2 && pos <= heap[0];
    }

    private void swap(int fpos, int spos) {
        int tmp;
        tmp = heap[fpos];
        heap[fpos] = heap[spos];
        heap[spos] = tmp;
    }

    //build heap from randomly ordered array of size n - O(n)
    public static void buildHeap(int[] H) {
        for (int i = H.length / 2; i > 0; i--) {
            siftDown(H, i);
        }
    }

    // A recursive function to max heapify the given
    // subtree. This function assumes that the left and
    // right subtrees are already heapified, we only need
    // to fix the root.
    private void maxHeapify(int pos) {
        if (isLeaf(pos))
            return;

        if (heap[pos] < heap[left(pos)] ||
                heap[pos] < heap[right(pos)]) {

            if (heap[left(pos)] > heap[right(pos)]) {
                swap(pos, left(pos));
                maxHeapify(left(pos));
            } else {
                swap(pos, right(pos));
                maxHeapify(right(pos));
            }
        }
    }

    // Inserts a new element to max heap
    public void insert(int element) {
        heap[++heap[0]] = element;

        // Traverse up and fix violated property
        int current = heap[0];
        while (current > 1 && heap[current] > heap[parent(current)]) {
            swap(current, parent(current));
            current = parent(current);
        }
    }

    public void bubbleUp(int[] H, int i) {
        while (i > 1 && H[i] > H[parent(i)]) {
            swap(H[i], H[parent(i)]);
            i = parent(i);
        }
    }

    public static void bubbleUp_V2(int[] H, int i) {
        int temp = H[i];
        while (i > 1 && temp > H[parent(i)]) {
            H[i] = H[parent(i)];
            i = parent(i);
        }
        H[i] = temp;
    }

    public static void siftDown(int[] H, int i) {

        if (print) System.out.println(Arrays.toString(H));

        int temp = H[i];
        //while has children
        while (H[0] >= left(i)) {
            int largest = left(i);

            if (H[0] >= right(i) && H[right(i)] > H[largest])
                largest = right(i);
            if (temp > H[largest]) {
                H[i] = temp;
                if (print) System.out.println(Arrays.toString(H));
                break;
            }
            H[i] = H[largest];
            if (print) System.out.println(Arrays.toString(H));
            i = largest;
        }
        H[i] = temp;
        if (print) System.out.println(Arrays.toString(H));
    }

    public static void siftDown_v2(int[] h, int i) {
        int leftChild = 2 * i;
        int rightChild = 2 * i + 1;
        int largerChild;
        if (rightChild < h.length && h[rightChild] > h[leftChild])
            largerChild = rightChild;
        else largerChild = leftChild;

        if (largerChild < h.length && h[largerChild] > h[i]) {
            int temp = h[i];
            h[i] = h[largerChild];
            h[largerChild] = temp;
            siftDown_v2(h, largerChild);
        }

    }

    public void removeMax() {
        heap[1] = heap[heap[0]--];
        int i = 1;
        while (i * 2 <= heap[0]) {
            int nextPos = getIndexOfMax(left(i), right(i));
            swap(i, nextPos);
            i = nextPos;
        }
    }

    private int getIndexOfMax(int i, int j) {
        return heap[i] > heap[j] ? i : j;
    }

    public void print() {
        for (int i = 1; i <= heap[0] / 2; i++) {
            System.out.print(" PARENT : " + heap[i] + " LEFT CHILD : " +
                    heap[2 * i] + " RIGHT CHILD :" + heap[2 * i + 1]);
            System.out.println();
        }
    }

    public int[] mergeHeaps(int[] h1, int[] h2) {
        int[] H = new int[h1[0] + h2[0] + 1];
        System.arraycopy(h1, 1, H, 1, h1[0]);
        System.arraycopy(h2, 1, H, h1[0] + 1, h2[0]);
        buildHeap(H);
        return H;
    }

    // Remove an element from max heap
    public int extractMax() {
        int popped = heap[1];
        heap[1] = heap[heap[0]--];
        maxHeapify(1);
        return popped;
    }

}
