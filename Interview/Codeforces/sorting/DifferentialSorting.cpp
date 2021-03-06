/**
 C. Differential Sorting
time limit per test2 seconds
memory limit per test256 megabytes
inputstandard input
outputstandard output
You are given an array ๐ of ๐ elements.

Your can perform the following operation no more than ๐ times: Select three indices ๐ฅ,๐ฆ,๐ง (1โค๐ฅ<๐ฆ<๐งโค๐) and replace ๐๐ฅ with ๐๐ฆโ๐๐ง. After the operation, |๐๐ฅ| need to be less than 1018.

Your goal is to make the resulting array non-decreasing. If there are multiple solutions, you can output any. If it is impossible to achieve, you should report it as well.

Input
Each test contains multiple test cases. The first line will contain a single integer ๐ก (1โค๐กโค10000) โ the number of test cases. Then ๐ก test cases follow.

The first line of each test case contains a single integer ๐ (3โค๐โค2โ105) โ the size of the array ๐.

The second line of each test case contains ๐ integers ๐1,๐2,โฆ,๐๐ (โ109โค๐๐โค109), the elements of ๐.

It is guaranteed that the sum of ๐ over all test cases does not exceed 2โ105.

Output
For each test case, print โ1 in a single line if there is no solution. Otherwise in the first line you should print a single integer ๐ (0โค๐โค๐) โ number of operations you performed.

Then the ๐-th of the following ๐ lines should contain three integers ๐ฅ,๐ฆ,๐ง (1โค๐ฅ<๐ฆ<๐งโค๐)โ description of the ๐-th operation.

If there are multiple solutions, you can output any. Note that you don't have to minimize the number of operations in this task.

3
5
5 -4 2 -1 2
3
4 3 2
3
-3 -2 -1

 */
#include<iostream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
using namespace std;

//gcc optimization
#pragma GCC optimize("Ofast")
#pragma GCC optimize "trapv"
#define fast(); ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << endl;
#else
#define debug(x)
#endif

bool issorted(ll *a,ll n)
{
    for(ll i = 1;i<n;i++)
    {
        if(a[i]<a[i-1])
            return 0;
    }
    return 1;
}

void solve() {
    ll n;
    cin>>n;
    ll a[n];
    for(ll i = 0;i<n;i++)
    {
        cin>>a[i];
    }
    if(issorted(a,n))
    {
        cout<<"0\n";
        return;
    }
    if(a[n-2]>a[n-1])
    {
        cout<<"-1\n";
        return;
    }
    ll val = a[n-2]-a[n-1];
    if(!issorted(a,n) && val >a[n-2])
    {
        cout<<"-1\n";
        return;
    }
    cout<<n-2<<"\n";
    for(ll i = 0;i<n-2;i++)
    {
        cout<<i+1<<" "<<n-1<<" "<<n<<"\n";
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    freopen("error1.txt","w",stderr);
#endif
    fast()

    int testCase = 0;
    cin >> testCase;
    while (testCase > 0) {
        solve();
        testCase--;
    }

#ifndef ONLINE_JUDGE
    cout << "\nTime Elapsed : " << 1000 * (lld)clock() / (lld)CLOCKS_PER_SEC
         << " ms\n";
#endif
    return 0;
}