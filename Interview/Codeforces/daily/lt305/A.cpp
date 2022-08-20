#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

class SegmentTree {
private:
    size_t size;
    ll result;
    vector<ll> tree;
public:
    SegmentTree(vector<int> &arr, const ll _result) : result(_result) {
        size = arr.size();
        tree.assign(size << 1, result);
        copy(arr.begin(), arr.end(), tree.begin() + size);
        for (int i = size - 1; i > 0; i--) {
            tree[i] = method(tree[i << 1], tree[i << 1 | 1]);
        }
    }
    ll method(ll a, ll b) {
        return a + b;
    }
    ll query(size_t l, size_t r) {
        ll res = result;
        l += size;
        r += size;
        while (l <= r) {
            if (l & 1) res = method(res, tree[l++]);
            if (r & 1 ^ 1) res = method(res, tree[r--]);
            l >>= 1;
            r >>= 1;
        }
        return res;
    }
    void update(size_t position, const ll newValue) {
        position += size;
        tree[position] = newValue;
        while (position > 0) {
            position >>= 1;
            tree[position] = method(tree[position << 1], tree[position << 1 | 1]);
        }
    }
};
ll summ (ll a, ll b) {
    return a + b;
}
class Solution {
public:
    vector<long long> maximumSegmentSum(vector<int>& nums, vector<int>& removeQueries) {
        vector<ll> ans;
        set<pair<int, int>> lines;
        lines.insert(make_pair(0, nums.size() - 1));
        SegmentTree seg(nums, 0);
        for (auto& x : removeQueries) {
            ll mx = 0ll;
            set<pair<int, int>> newLines;
            for (auto line:lines) {
                if (x >= line.first && x <= line.second) {
                    if (line.first < x) {
                        newLines.insert(make_pair(line.first, x-1));
                        mx = max(seg.query(line.first, x - 1), mx);
                    }
                    if (line.second > x) {
                        newLines.insert(make_pair(x+1, line.second));
                        mx = max(seg.query(line.first+1, line.second), mx);
                    }
                } else {
                    mx = max(seg.query(line.first, line.second), mx);
                    newLines.insert(line);
                }
            }
            lines = newLines;
            ans.push_back(mx);
        }

        return ans;
    }
};

int main() {
    Solution s;
    vector<int> a{1,2,5,6,1} , b {0,3,2,4,1};
    cout << s.maximumSegmentSum(a, b) << endl;
    cout << "1" << endl;
}