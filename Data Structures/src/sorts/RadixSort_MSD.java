package sorts;

import java.util.Arrays;

public class RadixSort_MSD {
    private static final int R = 256;
    private static final int CUTOFF = 15;

    public static void sort(String[] a) {
        int N = a.length;
        String[] aux = new String[N];
        sort(a, 0, N - 1, 0, aux);
    }

    private static int charAt(String s, int d) {
        return d == s.length() ? -1 : s.charAt(d);
    }

    private static void sort(String[] a, int lo, int hi, int d, String[] aux) {

        if (hi <= lo + CUTOFF) {
            insertion(a, lo, hi, d);
            return;
        }

        int[] count = new int[R + 2];
        for (int i = lo; i <= hi; i++) {
            count[charAt(a[i], d) + 2]++;
        }

        for (int r = 0; r < R + 1; r++)
            count[r + 1] += count[r];

        for (int i = lo; i <= hi; i++) {
            aux[count[charAt(a[i], d) + 1]++] = a[i];
        }

        if (hi + 1 - lo >= 0) System.arraycopy(aux, 0, a, lo, hi + 1 - lo);


        for (int r = 0; r < R; r++)
            sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
    }


    private static void insertion(String[] a, int lo, int hi, int d) {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j - 1], d); j--)
                swap(a, j, j - 1);
    }

    private static void swap(String[] a, int i, int j) {
        String temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }

    private static boolean less(String v, String w, int d) {
        assert v.substring(0, d).equals(w.substring(0, d));
        return v.substring(d).compareTo(w.substring(d)) < 0;
    }

    public static void main(String[] args) {
        String[] a = {"Hello", "world", "java", "j2ee"};
        System.out.println("List of items from array before sorting: " + Arrays.toString(a));
        sort(a);
        System.out.println("List of items from array after sorting: " + Arrays.toString(a));

    }

}