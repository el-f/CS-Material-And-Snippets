package structures.stacks;

import java.util.*;

public class Stacks {
    public static void main(String[] args) {
        Stack stack = new Stack();
        for (int i = 0; i < 5; i++) {
            stack.push(i);
        }

        System.out.println(stack.get(stack.size() - 5));  // java way
        stack.forEach(System.out::println);             //

        for (int i = 0; i < 4; i++) {
            stack.pop();
        }
        int i = (int) stack.pop();
        System.out.println(i);
    }

    static int getN(Stack stack, int n) {
        int a = 0;
        Stack s2 = new Stack();
        for (int i = 0; i < n - 1; i++) {
            a = (int) stack.pop();
            s2.push(a);
        }
        for (int i = 0; i < n - 1; i++) {
            stack.push(s2.pop());
        }
        return a;
    }

}
