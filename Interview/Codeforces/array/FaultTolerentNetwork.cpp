#include <bits/stdc++.h>

using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

void solve() {
    int n;cin>>n;
    vector<ll>a(n),b(n);
    for(int i =0 ; i < n;i++){
        cin>>a[i];
    }
    for(int i =0 ; i < n;i++){
        cin>>b[i];
    }
    ll ans = abs(a[0] - b[0]) + abs(b[n-1] - a[n-1]);
    ll ans1 = LONG_MAX , ans2 = LONG_MAX;
    for(int i =0 ; i <n;i++){
        ans1 = min(ans1,abs(b[0] - a[i]));
        ans2 = min(ans2,abs(b[n-1] - a[i]));
    }
    ll ans3 = LONG_MAX , ans4 = LONG_MAX;
    for(int i =0 ; i <n;i++){
        ans3 = min(ans3,abs(a[0] - b[i]));
        ans4 = min(ans4,abs(a[n-1] - b[i]));
    }
    // cout<<ans1<< " " <<ans2<< " "<<ans3<<" "<<ans4<<" "<<endl;;

    ll ans8 =  abs(a[0] - b[n-1]) + abs(a[n-1] - b[0]);
    ll res = ans1+ans2+ans3+ans4;
    res = min(res,ans);
    res = min(res,ans8);
    res = min(res,abs(a[0] - b[0]) + ans2+ans4);
    res = min(res,abs(a[n-1] - b[n-1])+ ans1+ans3);
    res = min(res,abs(a[0] - b[n-1]) + ans4 + ans1);
    res = min(res,abs(a[n-1] - b[0]) + ans2 + ans3);
    cout<<res<<endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("../data/input_FTN.txt", "r", stdin);
    freopen("../data/output_FTN.txt", "w", stdout);
    freopen("../data/error_FTN.txt", "w", stderr);
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