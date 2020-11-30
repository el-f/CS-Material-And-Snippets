package structures.stacks;

public class TwoStacksOneArray {

    static int[] arr;
    static int size1 = 0, size2 = 0;

    public static void main(String[] args) throws Exception {
        TwoStacksOneArray twoSt = new TwoStacksOneArray(100);
        //firstStack
        twoSt.push(true, 5);
        twoSt.push(true, -1);
        twoSt.push(true, 29);
        twoSt.push(true, 38);
        //secondStack
        twoSt.push(false, 99);
        twoSt.push(false, 123);
        twoSt.push(false, 251);

        //top
        System.out.println(twoSt.top(true));
        System.out.println(twoSt.top(false));
        //pop
        System.out.println(twoSt.pop(true));
        System.out.println(twoSt.pop(true));
        System.out.println(twoSt.pop(false));
        System.out.println(twoSt.pop(true));
        System.out.println(twoSt.pop(false));
        System.out.println(twoSt.pop(false));
        System.out.println(twoSt.pop(true));
    }


    TwoStacksOneArray(int totalSize) {
        arr = new int[totalSize];
    }

    boolean isFull() {
        return size1 + size2 == arr.length;
    }

    boolean isAllEmpty() {
        return size1 == 0 && size2 == 0;
    }

    boolean isStackOneEmpty() {
        return size1 == 0;
    }

    boolean isStackTwoEmpty() {
        return size2 == 0;
    }

    boolean push(boolean firstStack, int num) {
        if (isFull())
            return false;
        if (firstStack) arr[size1++] = num;
        else arr[arr.length - size2++ - 1] = num;
        return true;
    }

    int pop(boolean firstStack) throws Exception {
        return getNumFromStack(firstStack, true);
    }

    int top(boolean firstStack) throws Exception {
        return getNumFromStack(firstStack, false);
    }

    int getNumFromStack(boolean firstStack, boolean pop) throws Exception {
        if (firstStack && !isAllEmpty()) {
            if (pop) return arr[--size1];
            else return arr[size1 - 1];
        } else if (!isAllEmpty()) {
            if (pop) return arr[arr.length - --size2 - 1];
            else return arr[arr.length - size2];
        } else throw new Exception();
    }


}

