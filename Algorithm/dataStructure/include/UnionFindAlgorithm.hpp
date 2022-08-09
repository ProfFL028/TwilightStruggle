//
// Created by 方笠 on 2022/8/9.
//

#ifndef DATASTRUCTURE_UNIONFINDALGORITHM_HPP
#define DATASTRUCTURE_UNIONFINDALGORITHM_HPP

#include <iostream>
#include <vector>

/**
 * Union-Find Algorithms
 *
 */

template<int N>
class UnionFindSet {
public:
    UnionFindSet() {
        nodes.resize(N);
        for (int i = 0; i < N; i++) {
            nodes[i] = i;
        }
    }
    virtual ~UnionFindSet() {
        nodes.clear();
    }

    /**
     * Reset node that are equals to node[p] to node[q].
     * O(N*M)
     * @param p
     * @param q
     */
    void connect1(const int&p , const int& q) {
        if (nodes[p] == nodes[q]) return ;

        int t = nodes[p];
        for (int i = 0; i < N; i++) {
            if (nodes[i] == t)
                nodes[i] = nodes[q];
        }
    }

    /**
     * A little faster connect method.
     * @param p
     * @param q
     */
    void connect2(const int& p, const int& q) {
        int pp = nodes[p];
        while (pp != nodes[pp])
            pp = nodes[pp];
        int qq = nodes[q];
        while (qq != nodes[qq])
            qq = nodes[qq];

        if (pp == qq)
            return ;

        nodes[pp] = qq;
    }

    /**
     * path compression
     * @param p
     * @param q
     */
    void connect(const int& p, const int& q) {
        if (p < q)
            connect(q, p);
        int pp = p;
        while (pp != nodes[pp]) {
            nodes[pp] = nodes[nodes[pp]];
            pp = nodes[pp];
        }
        int qq = q;
        while (qq != nodes[qq]) {
            nodes[qq] = nodes[nodes[qq]];
            qq = nodes[qq];
        }

        if (pp == qq)
            return ;
        nodes[pp] = qq;
    }

    friend std::ostream& operator<<(std::ostream& out, UnionFindSet<N> ufs) {
        out << "{";
        for (int i = 0; i < N; i++) {
            out << i << " -> " << ufs.nodes[i] << ",\n";
        }
        out << "\b}";
        return out;
    }
private:
    std::vector<int> nodes;
};

#endif //DATASTRUCTURE_UNIONFINDALGORITHM_HPP
