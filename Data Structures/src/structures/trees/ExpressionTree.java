package structures.trees;

import java.util.Stack;

class ExpressionTree {

    public static void main(String[] args) {
        ExpressionTree et = new ExpressionTree();
        String postfix = "ab+ef*g*-";
        char[] charArray = postfix.toCharArray();
        Node root = et.constructTree(charArray);
        System.out.println("infix expression is");
        et.inorder(root);

    }

    // A utility function to check if 'c'
    // is an operator
    boolean isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    // Utility function to do inorder traversal
    void inorder(Node t) {
        if (t != null) {
            inorder(t.left);
            System.out.print(t.value + " ");
            inorder(t.right);
        }
    }

    // Returns root of constructed tree for given
    // postfix expression
    Node constructTree(char[] postfix) {
        Stack<Node> st = new Stack<>();
        Node t, t1, t2;

        // Traverse through every character of
        // input expression
        for (char c : postfix) {

            // If operand, simply push into stack
            if (!isOperator(c)) {
                t = new Node(c);
                st.push(t);
            } else // operator
            {
                t = new Node(c);

                // Pop two top nodes
                // Store top
                t1 = st.pop();      // Remove top
                t2 = st.pop();

                //  make them children
                t.right = t1;
                t.left = t2;

                // System.out.println(t1 + "" + t2);
                // Add this subexpression to stack
                st.push(t);
            }
        }

        // only element will be root of expression
        // tree
        t = st.peek();
        st.pop();

        return t;
    }
}