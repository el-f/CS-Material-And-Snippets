package Threads;

import java.util.concurrent.*;

// 2 solutions for this kata: 549e70e994e517ed8b00043e

@SuppressWarnings("all")
public class MultipleThreadsOrderedCounting {

    // The new and better way to do it
    public static void countInThreads_BETTERWAY(Counter counter) {

        ExecutorService[] execs = new ExecutorService[3];
        for (int i = 0; i < 3; i++) {
            execs[i] = Executors.newFixedThreadPool(1);
        }

        try {
            for (int i = 1; i <= 100; i++) {
                int n = i;
                Runnable task = () -> counter.count(n);
                execs[n % 3].submit(task).get();
            }

            for (int i = 0; i < 3; i++) {
                execs[i].shutdown();
                while (!execs[i].awaitTermination(1, TimeUnit.SECONDS))
                    System.out.println("terminating...");
            }
        } catch (InterruptedException | ExecutionException e) {
            throw new Error("can't happen", e);
        }
    }

    /****************************************************************************/

    // the classic but cumbersome way to do it
    public static void countInThreads_OLDWAY(Counter counter) {
        Count count = new Count(counter);
        Thread t1 = new Thread(count, "1");
        Thread t2 = new Thread(count, "2");
        Thread t3 = new Thread(count, "3");

        t1.start();
        t2.start();
        t3.start();

        try {
            t1.join();
            t2.join();
            t3.join();
        } catch (InterruptedException e) { /*ignore*/ }
    }

    public static class Count implements Runnable {
        private final Counter counter;
        static int working;

        public Count(Counter counter) {
            this.counter = counter;
            working = 1;
        }

        @Override
        public synchronized void run() {
            int threadId = Integer.parseInt(Thread.currentThread().getName());
            for (int i = 1; i <= 100; i++) {
                if (i % 3 == threadId % 3) {
                    while (working != threadId) {
                        try {
                            wait();
                        } catch (InterruptedException e) { /*ignore*/ }
                    }
                    counter.count(i);
                    working = (working == 3) ? 1 : working + 1;
                    notifyAll();
                }
            }
        }
    }

    static abstract class Counter {
        abstract void count(int i);
    }
}

