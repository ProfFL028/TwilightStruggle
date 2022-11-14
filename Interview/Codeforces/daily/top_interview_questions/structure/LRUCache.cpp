//https://leetcode.cn/leetbook/read/top-interview-questions/xmsw5r/
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;
class LRUCache {
public:
    LRUCache(int capacity) {
        n = capacity;
    }

    int get(int key) {
        if (mp.count(key)) {
            if (mp[key].second != order.size() - 1) {
                order[mp[key].second] = -1;
                order.push_back(key);
                mp[key] = make_pair(mp[key].first, order.size() - 1);
            }
            return mp[key].first;
        }
        return -1;
    }

    void put(int key, int value) {
        if (mp.count(key)) {
            order[mp[key].second] = -1;
            order.push_back(key);
            mp[key] = make_pair(value, order.size()-1);
        } else {
            if (mp.size() < n) {
                order.push_back(key);
                mp[key] = make_pair(value, order.size()-1);
            } else {
                while (order[id] == -1) id++;

                mp.erase(order[id]);
                order[id] = -1;
                order.push_back(key);
                mp[key] = make_pair(value, order.size()-1);
            }
        }
    }
    unordered_map<int, pair<int, int>> mp;
    vector<int> order;
    int n;
    int id = 0;
};

int main() {
    vector nums = {1,1,2,3,5,7,2,3};
    nums.erase(unique(nums.begin(), nums.end()), nums.end());
    for (auto n: nums) {
        cout << n << " ";
    }
    cout << endl;
    LRUCache cache(3);
    cache.put(1,1);
    cache.put(2,2);
    cache.put(3,3);
    cache.put(4,4);
    cache.get(4);
    cache.get(3);
    cache.get(2);
    cache.get(1);
    cache.put(5, 5);
    cache.get(1);
    cache.get(2);
    cache.get(3);
    cache.get(4);
    cache.get(5);
    return 0;
}