package Threads;

// Like Q1, but this time we use join to print the sum.
public class Join {

    public static void main(String[] args) {
        Print p1 = new Print(100_000);
        Print p2 = new Print(100_000);
        Thread t1 = new Thread(p1, "t1");
        Thread t2 = new Thread(p2, "t2");
        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            // Ignore
        }

        long sum1 = p1.getSum();
        long sum2 = p2.getSum();
        System.out.println(sum1);
        System.out.println(sum2);

    }

    public static class Print implements Runnable {

        private final int n;
        private long sum;

        public Print(int n) {
            this.n = n;
        }

        public long getSum() {
            return sum;
        }

        @Override
        public void run() {
            for (int i = 1; i <= n; i++)
                sum += i;
        }

    }
}
