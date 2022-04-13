#include <iostream>
#include <vector>
#include "SegmentTree.h"

using namespace std;
using namespace tree;

int main() {
    vector<int> data;

    data.push_back(5); // 0
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(8); // 5
    data.push_back(9);
    data.push_back(6);
    data.push_back(7);

    SegmentTree<int> sumTree(data, [](const int &v1, const int &v2) { return v1 + v2; }, 0);
    cout << sumTree.query(5, 7) << endl;
    cout << sumTree.query(1, 7) << endl;
    sumTree.update(2, 10);
    cout << sumTree.query(5, 7) << endl;
    cout << sumTree.query(1, 7) << endl;


    SegmentTree<int> minTree(data, [](const int &v1, const int &v2) { return min(v1, v2); }, INT_MAX);
    cout << minTree.query(5, 7) << endl;
    cout << minTree.query(1, 7) << endl;
    minTree.update(1, 10);
    cout << minTree.query(5, 7) << endl;
    cout << minTree.query(1, 7) << endl;
    return 0;
}