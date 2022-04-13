// codeforces: https://codeforces.com/contest/1665/problem/E

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

template<class T, class F=function<T(const T &, const T &)>>
class SegmentTree {
private:
    // vector's original size
    size_t size;
    // method of the segment function.
    F method;
    T result; // default value, for sum function it is 0, for min function, it is INT_MAX, for max function, it is INT_MIN.
    // optimized segment tree.
    vector<T> tree;
public:
    /**
     * Store the segment result in tree format. The tree contains 2* size elements, where 0th is useless.
     * tree[n+i] stores arr[i] only where 0<=i<n.
     * tree[i] stores the result of method(tree[i<<1], tree[i<<1|1]) that is segment from i<<1-n to i<<1 - n + 1 if  n/2<=i < n...
     * This is a optimized segment tree.
     * @param arr array of the original data.
     * @param f method.
     * @param result default value in the segment tree.
     */
    SegmentTree(vector<T> &arr, const F &f, const T _result) : method(f), result(_result) {
        size = arr.size();
        tree.assign(size << 1, result);
        copy(arr.begin(), arr.end(), tree.begin() + size);
        for (int i = size - 1; i > 0; i--) {
            tree[i] = method(tree[i << 1], tree[i << 1 | 1]);
        }
    }

    /**
     * query from the tree.
     * @param l
     * @param r
     * @return
     */
    T query(size_t l, size_t r) {
        T res = result;
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

    /**
     *
     * @param position
     * @param newValue
     */
    void update(size_t position, const T newValue) {
        position += size;
        tree[position] = newValue;
        while (position > 0) {
            position >>= 1;
            tree[position] = method(tree[position << 1], tree[position << 1 | 1]);
        }
    }
};

void solve() {
    size_t n;
    cin >> n;
    vector<pair<int, int>> arr(n);
    for (size_t i = 0; i < n; i++) {
        cin >> arr[i].first;
        arr[i].second = i;
    }
    SegmentTree<pair<int, int>> tree(arr, [](pair<int, int> v1, pair<int, int> v2) { return min(v1, v2); },
                                     {INT_MAX, -1});

    size_t k;
    cin >> k;
    while (k--) {
        size_t l, r;
        cin >> l >> r;
        --l, --r;

        vector<int> checkList;
        // the minus value of bitwise can only be in the minial 31 values.
        for (int i = 0; i <= 30; i++) {
            pair<int, int> x = tree.query(l, r);
            if (x.first == INT_MAX)
                break;
            checkList.push_back(x.second);
            tree.update(x.second, {INT_MAX, x.second});
        }
        // fix the tree.
        for (auto & i : checkList) {
            tree.update(i, arr[i]);
        }
        // find the answer.
        int ans = INT_MAX;
        for (size_t i = 0; i < checkList.size()-1; i++) {
            for (size_t j = i+1; j < checkList.size(); j++) {
                ans = min(ans, arr[checkList[i]].first | arr[checkList[j]].first);
            }
        }
        cout << ans << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input.txt", "r", stdin);
    freopen("../data/output.txt", "w", stdout);
    freopen("../data/error.txt", "w", stderr);
#endif
    fast()

    int testCase = 1;
    cin >> testCase;
    while (testCase > 0) {
        solve();
        testCase--;
    }

#ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed : " << 1000 * (lld) clock() / (lld) CLOCKS_PER_SEC
         << " ms\n";
#endif
    return 0;
}