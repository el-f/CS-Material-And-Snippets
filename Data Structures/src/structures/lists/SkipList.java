package structures.lists;

/* SI 486H Spring 2016
   This is a skeleton for a skip list class that only supports
   insertion of height-1 nodes.

   Nodes are stored in "towers" which contain a list of forward-facing
   links ("flinks"), as well as a key and a value.

   To demo on a small random example, run 'javac SkipList.java && java SkipList"
*/

import java.util.*;

public class SkipList<V> {
    private class Tower {
        double key;
        V value;
        ArrayList<Tower> flinks;

        Tower(int h, double key, V value) {
            this.key = key;
            this.value = value;
            this.flinks = new ArrayList<>(Collections.nCopies(h + 1, (Tower) null));
        }
    }

    Tower start;
    Tower end;
    int size = 0;

    public SkipList() {
        this.start = new Tower(0, Double.NEGATIVE_INFINITY, null);
        this.end = new Tower(0, Double.POSITIVE_INFINITY, null);
        this.start.flinks.set(0, this.end);
    }

    public int height() {
        return this.start.flinks.size() - 1;
    }

    public int size() {
        return this.size;
    }

    public void insert(double key, V value) {
        int h = 1; // TODO: choose height randomly!
        Tower newTower = new Tower(h, key, value);

        // Grow height of start/end as needed
        while (h >= this.height()) {
            this.start.flinks.add(this.end);
            this.end.flinks.add(null);
        }

        Tower currentTower = this.start;
        int level = currentTower.flinks.size() - 1;
        while (level >= 0) {
            if (key > currentTower.flinks.get(level).key) {
                // Move right if we can on this level
                currentTower = currentTower.flinks.get(level);
            } else {
                // Otherwise go down a level
                if (level <= h) {
                    // Insert the new tower on this level
                    newTower.flinks.set(level, currentTower.flinks.get(level));
                    currentTower.flinks.set(level, newTower);
                }
                level -= 1;
            }
        }

        this.size += 1;
    }

    public String toString() {
        /* Returns a nice pretty representation of the skip list */
        StringBuilder stb = new StringBuilder();
        for (int level = this.height(); level >= 0; --level) {
            Tower currentTower = this.start;
            while (currentTower != this.end) {
                String rep = "(k=" + currentTower.key + " , v=" + currentTower.value + ")";
                if (level >= currentTower.flinks.size()) {
                    stb.append("-".repeat(rep.length()));
                } else {
                    stb.append(rep);
                }
                stb.append("--");
                currentTower = currentTower.flinks.get(0);
            }
            stb.append("(k=").append(currentTower.key).append(" , v=").append(currentTower.value).append(")\n");
        }
        return stb.toString();
    }

    public static void main(String[] args) {
        Random r = new Random();
        // Randomly insert 10 numbers and print the resulting skip list
        SkipList<Integer> S = new SkipList<>();
        for (int i = 0; i < 7; ++i) {
            S.insert(r.nextInt(100), r.nextInt(120));
        }
        System.out.println(S);

    }
}