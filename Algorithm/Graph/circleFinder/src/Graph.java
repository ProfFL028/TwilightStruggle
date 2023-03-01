import java.io.*;
import java.sql.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class Graph {

    Graph(String fileName) {
        buildFromFile(fileName);
    }

    List<List<String>> findCircle() {
        result = new ArrayList<>();
        preNode = new HashMap<>();
        for (String node : graph.keySet()) {
            if (color.get(node) == 0) {
                dfs(node);
            }
        }

        return result;
    }

    private HashMap<String, List<String>> graph;

    private List<List<String>> result;
    private HashMap<String, Integer> color;
    private HashMap<String, String> preNode;

    public static void main(String[] args) {
        String fileName = "D:\\TwilightStruggle\\CCPP\\2DDrawing\\cmake-build-debug\\danbao.csv";
        Graph graph = new Graph(fileName);
        List<List<String>> circles = graph.findCircle();

        for (List<String> circle : circles) {
            StringBuilder sb = new StringBuilder();
            for (String s : circle) {
                sb.append(s).append("->");
            }
            sb.delete(sb.length() - 2, sb.length());
            System.out.println(sb);
        }
    }

    private void buildFromFile(String fileName) {
        graph = new HashMap<>();
        color = new HashMap<>();
        BufferedReader fileReader = null;
        try {
            fileReader = new BufferedReader(new FileReader(fileName));
            fileReader.lines().forEach(this::buildGraph);
        } catch (FileNotFoundException e) {
            System.out.println(fileName + " 读取失败！");
        }
    }

    private void buildGraph(String line) {
        String guarantor;
        int lineSize = line.length();
        int idx = 0;
        int i = 0;
        while (i < lineSize && line.charAt(i) == ' ') {
            i++;
        }
        idx = i;
        while (i < lineSize && line.charAt(i) != ' ' && line.charAt(i) != ',') {
            i++;
        }
        guarantor = line.substring(idx, i);
        graph.put(guarantor, new ArrayList<>());
        color.put(guarantor, 0);
        while (i < lineSize && line.charAt(i) == ' ' || line.charAt(i) == ',') {
            i++;
        }
        idx = i;
        while (i < lineSize) {
            if (line.charAt(i) == ' ' || line.charAt(i) == '|') {
                if (i - idx > 5)
                    graph.get(guarantor).add(line.substring(idx, i));
                idx = i + 1;
            }
            i++;
        }
        if (i - idx > 5) {
            graph.get(guarantor).add(line.substring(idx, i));
        }
    }

    private void dfs(String curNode) {
        color.put(curNode, 1);
        if (graph.containsKey(curNode)) {
            for (String nxt : graph.get(curNode)) {
                if (color.containsKey(nxt)) {
                    if (color.get(nxt) == 0) {
                        preNode.put(nxt, curNode);
                        dfs(nxt);
                    } else if (color.get(nxt) == 1) {
                        buildCircle(nxt);
                    }
                }
            }
        }
        color.put(curNode, 2);
    }

    private void buildCircle(String node) {
        if (!preNode.containsKey(node))
            return ;
        List<String> circle = new ArrayList<>();
        circle.add(node);
        while (preNode.containsKey(node)) {
            node = preNode.get(node);
            circle.add(node);
        }
        List<String> reverse = new ArrayList<>();
        for (int i = circle.size() - 1; i >= 0; i--) {
            reverse.add(circle.get(i));
        }

        result.add(reverse);
    }
}