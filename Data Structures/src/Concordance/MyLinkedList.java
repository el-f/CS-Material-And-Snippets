package Concordance;

public class MyLinkedList {
    private final LLNode head;
    private LLNode tail;
    public int size;

    public static boolean breakOutputLine = true;

    private static class LLNode {
        int data;
        LLNode next;

        LLNode(int _data) {
            this(_data, null);
        }

        LLNode(int _data, LLNode _next) {
            data = _data;
            next = _next;
        }
    }

    public MyLinkedList(int headData) {
        head = new LLNode(headData);
        tail = head;
        size = 1;
    }

    // O(1)
    public void insert(int _data) {
        tail.next = new LLNode(_data);
        tail = tail.next;
        size++;
    }

    //O(n) when n is the number of nodes
    public String toString(int indent) {
        if (head == null) return "[]";
        LLNode cur = head;
        StringBuilder sb = new StringBuilder();
        int counter = 0;
        String sizeStr = "(" + size + " instance" + (size > 1 ? 's' : "") + ") - [";
        sb.append(sizeStr);
        indent += sizeStr.length();
        while (cur.next != null) {
            sb.append(cur.data).append(", ");
            cur = cur.next;

            //every set interval go down a line and indent - for nicer output
            if (breakOutputLine && ++counter % 30 == 0) {
                sb.append('\n');
                for (int i = 0; i < indent; i++) sb.append(" ");
            }
        }
        sb.append(cur.data).append("]");
        return sb.toString();
    }
}
