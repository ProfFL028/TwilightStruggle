// https://codeforces.com/contest/1656/problem/B

#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

const int maxLen = 10e6 + 5;
ll arr[maxLen];

bool bs(ll value, int start, int end) {
    if (value > 10e9L)
        return false;

    while (start <= end) {
        int mid = start + (end - start) / 2;
        if (arr[mid] > value) {
            end = mid - 1;
        } else if (arr[mid] < value) {
            start = mid + 1;
        } else {
            return true;
        }
    }
    return false;

    // recursive version.
//    if (start > end) {
//        return false;
//    }
//    int mid = start + (end - start) / 2; // avoid max_integer problem.
//    if (arr[mid] > value) {
//        return bs(value, start, mid - 1);
//    } else if (arr[mid] < value) {
//        return bs(value, mid+1, end);
//    } else {
//        return true;
//    }
}

void solve() {
    ll n, k;
    cin >> n >> k;
    bool isOk = false;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    for (int i = 0; i < n - 1; i++) {
        isOk = bs(arr[i] + k, i, n - 1);
        if (isOk) break;
    }


    if (isOk) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

/**
 * using set.!!
 * @return
 */
int slove2() {
    int n,k;
    cin>>n>>k;
    vector<int> v(n);
    for(int i=0;i<n;i++)
        cin>>v[i];
    sort(v.begin(),v.end());
    set<int> s;
    int flag=0;
    for(int i=0;i<n;i++){
        if(s.find(v[i]-k)!=s.end()){
            flag=1;
            break;
        }
        s.insert(v[i]);
    }
    if(flag) cout<<"YES\n";
    else cout<<"NO\n";
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