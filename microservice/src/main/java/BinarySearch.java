import java.util.*;

class Node {
    Node left, right;
    int data;

    Node(int newData) {
        left = right = null;
        data = newData;
    }
}

public class BinarySearch {
    public static void main(String[] args) {
        Node root = new Node(20);
        root.left = new Node(10);
        root.right = new Node(30);
        root.left.left = new Node(8);
        root.left.right = new Node(12);
        root.right.left = new Node(20);
        root.right.right = new Node(40);

        List<Integer> ints = new ArrayList();
        ints.add(79);
        ints.add(10);
        ints.add(20);
        ints.add(30);
        ints.add(40);

        for (int i : ints) {
            System.out.println(isPresent(root, i));
        }
    }
    static int isPresent(Node root, int value) {
        if (root == null) {
            return 0;
        }
        if (root.data == value) {
            return 1;
        } else if (value > root.data) {
            return isPresent(root.left, value);
        } else {
            return isPresent(root.right, value);
        }
    }

    public static void main2(String[] args) {
        List<String> values = new ArrayList<>();
        values.add("[()]");
        values.add("([{]})");
        values.add("]([)");
        values.add("({[]})");

        List<String> result = new ArrayList<>();
        Map<Character, Character> braces = new HashMap();
        braces.put(']', '[');
        braces.put(')', '(');
        braces.put('}', '{');
        for (String value : values) {
            Stack<Character> s = new Stack();
            boolean ans = true;
            for (char c : value.toCharArray()) {
                if (!braces.containsKey(c)) {
                    s.push(c);
                } else {
                    if (s.isEmpty() || braces.get(c) != s.peek()) {
                        ans = false;
                        break;
                    } else {
                        s.pop();
                    }
                }
            }
            if (ans && s.isEmpty()) {
                result.add("YES");
            } else {
                result.add("NO");
            }
        }

        for (String a : result) {
            System.out.println(a);
        }
    }
}
