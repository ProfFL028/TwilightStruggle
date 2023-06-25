import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;

public class Graph {

    Graph(String fileName) {
        buildFromFile(fileName);
    }

    List<List<String>> result = new ArrayList<>();
    Set<String> visited = new HashSet<>();
    List<String> path = new ArrayList<>();

    public List<List<String>> findCircles() {

        for (String key : graph.keySet()) {
            dfs(key);
        }

        return result;
    }

    private HashMap<String, List<String>> graph;

    public static void main(String[] args) {
        String fileName = "D:\\TwilightStruggle\\CCPP\\2DDrawing\\cmake-build-debug\\danbao.csv";
        Graph graph = new Graph(fileName);
        List<List<String>> circles = graph.findCircles();

        for (int i = 0; i < circles.size(); i++) {
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < circles.get(i).size(); j++) {
                sb.append(circles.get(i).get(j)).append("->");
            }
            sb.delete(sb.length() - 2, sb.length());
            System.out.println(sb);
        }
    }

    private void buildFromFile(String fileName) {
        graph = new HashMap<>();
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

    private void dfs(String node) {
        visited.add(node);
        path.add(node);

        if (graph.containsKey(node)) {
            for (String neighbor : graph.get(node)) {
                if (path.contains(neighbor)) {
                    int begin = path.indexOf(neighbor);
                    int end = path.size();
                    if (end - begin >= 2) {
                        List<String> circle = new ArrayList<>();
                        for (int i = begin; i < end; i++) {
                            circle.add(path.get(i));
                        }
                        result.add(circle);
                    }
                } else if (!visited.contains(neighbor)) {
                    dfs(neighbor);
                }
            }
        }

        path.remove(path.size() - 1);
        visited.remove(node);
    }

    private void buildCircle(String neighbor) {
        int begin = path.indexOf(neighbor);
        int end = path.size();
        result.add(path.subList(begin, end));
    }
}