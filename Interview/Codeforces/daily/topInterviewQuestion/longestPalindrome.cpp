#include <bit/stdc++.h>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.length();
        if (n == 1) return s;

        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int maxLeft = 0;
        int maxLength = 1;
        for (int right = 1; right < n; right++) {
            for (int left = 0; left <right; left++) {
                if (s[left] == s[right]) {
                    if (right - left <= 2)
                        dp[left][right] = true;
                    else
                        dp[left][right] = dp[left+1][right-1];

                    if (dp[left][right] && (right-left+1) > maxLength) {
                        maxLength = right - left + 1;
                        maxLeft = left;
                    }
                }
            }
        }
        return s.substr(maxLeft, maxLength);
    }
};

int main() {
    Solution solution;
    cout <<solution.longestPalindrome("bbc")  << endl;

    return 0;
}