
#ifndef DATASTRUCTURE_GRAPH_H
#define DATASTRUCTURE_GRAPH_H

#include <iostream>
#include <vector>

class Graph {
public:
    explicit Graph(const std::size_t &n) : n{n} {
        data.resize(n+1);
    }

    virtual ~Graph() {
        data.clear();
    }

    void init(std::istream &input);

    inline bool isVertexValid(const int &u) const {
        return u >= 1 && u <= n;
    }

    inline std::size_t degree(const std::size_t& u) const {
        return data[u].size();
    }

    inline std::vector<std::size_t> degreeSequence() const {
        std::vector<std::size_t> degrees(n+1,0);
        for (std::size_t i = 1; i <= n; i++) {
            degrees[i] = degree(i);
        }
        return degrees;
    }

    std::size_t edgeCount() const;

    bool isRegular() const;
    inline bool isConnected() const {
        for (std::size_t i = 1; i <= n; i++) {
            if (degree(i) == 0) {
                return false;
            }
        }
        return true;
    }

    inline bool isNeighborhood(const std::size_t& u, const std::size_t& v) const {
        return std::find(data[u].begin(), data[u].end(), v) == data[u].end();
    }

    // https://en.wikipedia.org/wiki/Graph_isomorphism_problem
    static bool isIsomorphicGraphs(const Graph& g1, const Graph& g2);

    bool isConnected(const std::size_t& u, const std::size_t& v) const;

    bool containsCircle() const;

private:
    std::vector<std::vector<int>> data;
    std::size_t n;
};



#endif //DATASTRUCTURE_GRAPH_H
