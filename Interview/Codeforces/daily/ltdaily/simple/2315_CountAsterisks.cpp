// https://leetcode.cn/problems/count-asterisks/
// 
#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int countAsterisks(string s) {
        bool isInPair = false;
        int ans = 0;
        for (auto & c : s) {
            if (!isInPair) {
                if (c == '*')
                    ans++;
                else if (c == '|')
                    isInPair = true;
            } else {
                if (c == '|')
                    isInPair = false;
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;

    return 0;
}
