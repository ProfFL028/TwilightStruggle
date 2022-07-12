#include "Graph.h"
#include <deque>

void Graph::init(std::istream &input) {
    std::size_t u, v;
    input >> u >> v;
    if (isVertexValid(u) && isVertexValid(v)) {
        data[u].push_back(v);
        data[v].push_back(u);
    }
}

std::size_t Graph::edgeCount() const {
    std::size_t result{0};
    for (auto i = 1; i <= n; i++) {
        result += degree(i);
    }
    return result / 2;
}

bool Graph::isIsomorphicGraphs(const Graph &g1, const Graph &g2) {
    if (g1.n == g2.n) {
        auto degreeSequence1 = g1.degreeSequence();
        auto degreeSequence2 = g2.degreeSequence();
        std::sort(degreeSequence1.begin(), degreeSequence1.end());
        std::sort(degreeSequence2.begin(), degreeSequence2.end());
        for (std::size_t i = 1; i <= g1.n; i++) {
            if (degreeSequence1[i] != degreeSequence2[i]) {
                return false;
            }
        }

        // check if they have the same number of circuit of particular length.
        return true;
    }

    return false;
}

bool Graph::isRegular() const {
    auto deg = degree(1);
    for (std::size_t i = 2; i <= n; i++) {
        if (deg != degree(i)) {
            return false;
        }
    }
    return true;
}

bool Graph::isConnected(const std::size_t &u, const std::size_t &v) const {
    std::vector<bool> visited(n + 1, false);
    std::deque<std::size_t> queue;
    queue.push_back(u);
    while (!queue.empty()) {
        auto cur = queue.front();
        queue.pop_front();
        visited[cur] = true;

        for (auto next: data[cur]) {
            if (next == v) {
                return true;
            }
            if (!visited[next]) {
                queue.push_back(next);
            }
        }
    }

    return false;
}

bool Graph::containsCircle() const {
    std::vector<bool> visited(n + 1, false);
    std::deque<std::pair<std::size_t, std::size_t>> queue;
    for (std::size_t i = 1; i <= n; i ++) {
        queue.push_back(std::make_pair(i, -1));
    }
    while (!queue.empty()) {
        auto cur = queue.front();
        queue.pop_front();
        if (cur.second == -1 && visited[cur.first])
            continue;
        visited[cur.first] = true;
        for (auto next : data[cur.first]) {
            if (next != cur.second)  {
                if (visited[next])
                    return true;
                else
                    queue.push_back(std::make_pair(next, cur.first));
            }
        }
    }
}
