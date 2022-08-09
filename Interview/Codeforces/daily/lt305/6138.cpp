#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int longestIdealString(string s, int k) {
        int f[26]{};
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            int mx = 0;
            for (int j = max(0, c - k); j <= min(25, c+k); j++) {
                mx = max(mx, f[j]);
            }
            f[c]=max(f[c], 1+mx);
        }
        queue<int> q;
        return *max_element(f, f+26);
    }
};

int main() {
    string s = "acfgbd";
    int k = 2;
    Solution solution;
    cout << solution.longestIdealString(s, k) << endl;
    vector<int> l;
}