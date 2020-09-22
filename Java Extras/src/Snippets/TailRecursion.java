package Snippets;

public class TailRecursion {
    public static void main(String[] args) {
        System.out.println(fact(4));
        System.out.println(tail_fact(4, 1));
    }

    //regular recursion - inefficient
    static int fact(int n) {
        if (n == 1)
            return 1;
        return n * fact(n - 1);
    }

    //tail recursion - more efficient
    static int tail_fact(int n, int m) {
        if (n == 1)
            return m;
        return tail_fact(n - 1, n * m);
    }

}
