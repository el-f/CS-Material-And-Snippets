package Snippets;

public class Ackermann {
    public static void main(String[] args) {
        for (int m = 0; m <= 3; m++)
            for (int n = 0; n <= 4; n++)
                System.out.println("for (" + m + "," + n + ") - " + Acker(m, n));
    }

    public static int Acker(int m, int n) {
        if (m == 0)
            return n + 1;
        if (n == 0)
            return Acker(m - 1, 1);
        return Acker(m - 1, Acker(m, n - 1));
    }
}
