package Threads;

// interrupt example
public class Interrupt {

    public static final boolean INTERRUPT = true;
    public static final boolean DETECT_INTERRUPT = false;

    public static void main(String[] args) {
        Print1 p1 = new Print1(5);
        Print2 p2 = new Print2(5);
        Thread t1 = new Thread(p1, "t1");
        Thread t2 = new Thread(p2, "t2");
        t1.start();
        t2.start();
        if (INTERRUPT) {
            t1.interrupt();
            t2.interrupt();
        }
    }

    public static class Print1 implements Runnable {

        private final int n;

        public Print1(int n) {
            this.n = n;
        }

        @Override
        public void run() {
            for (int i = 1; i <= n; i++) {
                System.out.println(i + "(" + Thread.currentThread().getName() + ")");
                if (DETECT_INTERRUPT && Thread.currentThread().isInterrupted()) return;
            }
        }

    }

    public static class Print2 implements Runnable {

        private int n;

        public Print2(int n) {
            this.n = n;
        }

        @Override
        public void run() {
            for (int i = 1; i <= n; i++) {
                System.out.println(i + "(" + Thread.currentThread().getName() + ")");
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e) {
                    return;
                }
            }
        }

    }

}
