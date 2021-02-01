package thread;

public class MaxThreads {
    private static final Object synchronizer = new Object();
    private static int count = 0;

    public static void main(String[] argv) {
        while (count < Integer.MAX_VALUE) {
            new Thread(() -> {
                synchronized (synchronizer) {
                    count += 1;
                    System.err.println("New thread #" + count);
                }
                for (; ; ) {
                    try {
                        Thread.sleep(1000);
                    } catch (Exception e) {
                        System.err.println(e);
                    }
                }
            }).start();
        }
    }
}