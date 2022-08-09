//
// Created by 方笠 on 2022/8/9.
//

#include <iostream>
#include "UnionFindAlgorithm.hpp"

using namespace std;

int main() {
    vector<pair<int,int>> nodes;
    nodes.push_back({0,2});
    nodes.push_back({1, 4});
    nodes.push_back({2, 5});
    nodes.push_back({3, 6});
    nodes.push_back({0, 4});
    nodes.push_back({6, 0});
    nodes.push_back({1, 3});

    UnionFindSet<10> ufs, ufs1, ufs2;

    for (auto& node: nodes) {
        ufs.connect(node.first, node.second);
        cout << "after connect " << node.first << " with " << node.second << endl;
        cout << ufs << endl;
    }
}