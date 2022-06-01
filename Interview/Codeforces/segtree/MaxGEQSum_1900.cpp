// codeforces:  https://codeforces.com/contest/1691/problem/D

#include <bits/stdc++.h>

using namespace std;

// gcc optimization (it may doesn't work)
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
const ll MOD = 1000000007;
#define print(v) cout << v.size(); for (auto& x: v) cout << x << " "; cout << endl;

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
    int n;
    cin >> n;
    vector<ll> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    if (n == 1) {
        cout << "YES" << endl;
        return;
    }
    vector<int> nextGreater(n, n), preGreater(n, -1);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && arr[s.top()] < arr[i]) {
            nextGreater[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    while (!s.empty()) {
        s.pop();
    }
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && arr[s.top()] < arr[i]) {
            preGreater[s.top()] = i;
            s.pop();
        }
        s.push(i);
    }
    vector<ll> prefixSum(n), suffixSum(n);
    prefixSum[0] = arr[0];
    for (int i = 1; i < n; i++) {
        prefixSum[i] = prefixSum[i - 1] + arr[i];
    }
    suffixSum[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        suffixSum[i] = suffixSum[i + 1] + arr[i];
    }

    SegmentTree<ll> prefixTree(prefixSum, [](ll l, ll r) { return max(l, r); }, LONG_LONG_MIN);
    SegmentTree<ll> suffixTree(suffixSum, [](ll l, ll r) { return max(l, r); }, LONG_LONG_MIN);

    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            if ((nextGreater[i] - 1 > i && prefixTree.query(i + 1, nextGreater[i] - 1) > prefixSum[i]) ||
                (preGreater[i] + 1 < i && suffixTree.query(preGreater[i] + 1, i - 1) > suffixSum[i])) {
                cout << "NO" << endl;
                return;
            }
        }
    }
    cout << "YES" << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../input.txt", "r", stdin);
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