package assignments._II;

public class LinkedLists_HW_A {

    //Q1
    public static Node getNodeForValue(Node head, int value) {
        Node cur = head;
        while (cur != null) {
            if (cur.data == value) break;
            cur = cur.next;
        }
        return cur;
    }

    //Q2
    public static int countOccurrences(Node head, int value) {
        if (head == null) return 0;
        return (head.data == value ? 1 : 0) + countOccurrences(head.next, value);
    }

    //Q3
    public static void deleteFirstOccur(Node head, int value) {
        Node prev = head;
        Node cur = head;
        while (prev != null && cur != null) {
            if (cur.data == value) {
                prev.next = cur.next;
                return;
            } else {
                prev = cur;
                cur = cur.next;
            }
        }
    }

    //Q4
    public static void deleteLastOccur(Node head, int value) {
        Node cur = head;
        Node found = null;
        while (cur != null) {
            if (cur.data == value)
                found = cur;
            cur = cur.next;
        }
        if (found != null) {
            for (cur = head; cur.next != found; )
                cur = cur.next;
            cur.next = found.next;
        }
    }

    //Q5
    public static void deleteAllOccur(Node head, int value) {
        Node prev = head;
        Node cur = head;
        while (prev != null && cur != null) {
            if (cur.data == value) {
                prev.next = cur.next;
            } else {
                prev = cur;
            }
            cur = cur.next;
        }
    }

    //Q6
    public static Node copyList(Node head) {
        Node copyHead = head == null ? null : new Node(head);
        Node copyCur = copyHead;
        Node originalHead = head;
        while (originalHead.next != null) {
            copyCur.next = new Node(originalHead.next);
            copyCur = copyCur.next;
            originalHead = originalHead.next;
        }
        return copyHead;
    }

    //testing
    public static void main(String[] args) {
        Node node = new Node(new Node(new Node(null, 3), 2), 1);

        //Q1
        System.out.println(node == getNodeForValue(node, 1));
        System.out.println(node.next == getNodeForValue(node, 2));
        System.out.println(node.next.next == getNodeForValue(node, 3));

        //Q2
        Node node2 =
                new Node(new Node(new Node(new Node(new Node(new Node(null,
                        2),
                        3),
                        3),
                        4),
                        2),
                        3);
        System.out.println(countOccurrences(node2, 3) == 3);

        //Q3_4_5
        Node dummy = new Node(node2, 0);
        System.out.println(dummy);

        deleteFirstOccur(dummy, 3);
        System.out.println(dummy);

        deleteLastOccur(dummy, 2);
        System.out.println(dummy);

        deleteAllOccur(dummy, 3);
        System.out.println(dummy);

        //Q6
        System.out.println(node);
        Node copy = copyList(node);
        System.out.println(copy);
        System.out.println(copy != node);
        System.out.println(node);
    }
}

class Node {
    Node next;
    int data;

    //for copying
    Node(Node copy) {
        if (copy == null) return;
        next = copy.next;
        data = copy.data;
    }

    Node(Node _next, int _data) {
        next = _next;
        data = _data;
    }

    public String toString() {
        return data + " " + (next != null ? next : "");
    }
}
