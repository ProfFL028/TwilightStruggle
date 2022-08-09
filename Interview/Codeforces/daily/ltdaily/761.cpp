#include <bits/stdc++.h>

using namespace std;
class Solution {
public:
    string makeLargestSpecial(string s) {
        if (s.length() <= 2) {
            return s;
        }
        vector<string> specials;
        int count = 0, pre = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '0') {
                count--;
                if (count == 0) {
                    specials.push_back("1" + makeLargestSpecial(s.substr(pre + 1, i - pre - 1)) +"0");
                    pre = i + 1;
                }
            }else {
                count++;
            }
        }

        sort(specials.begin(), specials.end(), greater<>());
        string ans = accumulate(specials.begin(), specials.end(), ""s);
        return ans;
    }
};

int main() {
    string s = "110110100100";
    Solution solution;
    cout << solution.makeLargestSpecial(s) << endl;
}