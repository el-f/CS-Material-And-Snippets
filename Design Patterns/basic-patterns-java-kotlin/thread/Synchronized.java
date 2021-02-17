package thread;

// synchronized example
public class Synchronized {

    public static void main(String[] args) {
        Print p = new Print(100000);
        Thread t1 = new Thread(p, "t1");
        Thread t2 = new Thread(p, "t2");
        t1.start();
        t2.start();
    }

    public static class Print implements Runnable {

        private final int n;

        public Print(int n) {
            this.n = n;
        }

        @Override
        public void run() {
            sum();
            sumV2();
        }

        public synchronized void sum() {
            long sum = 0;
            for (int i = 1; i <= n; i++)
                sum += i;

            System.out.println(sum);
        }

        public void sumV2() {
            synchronized (this) {
                long sum = 0;
                for (int i = 1; i <= n; i++)
                    sum += i;

                System.out.println(sum);
            }
        }

    }

}
