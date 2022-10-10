#include <bit/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s == "") return 0;

        int i = 0, j = 1;
        int n = s.length();
        unordered_set<char> st;
        st.insert(s[i]);
        int ans = 1;
        while (j < n) {
            if (st.find(s[j]) != st.end()) {
                ans = max(ans, j - i);
                for (; i < j; i++) {
                    if (s[i] == s[j]) break;
                    else st.erase(s[i]);
                }
                if (i < j) {
                    i++;
                }
            } else {
                st.insert(s[j]);
            }
            j++;
        }

        return max(ans, j-i);
    }
};

int main() {
    Solution solution;
    cout << solution.lengthOfLongestSubstring("abcabcabb") << endl;
    return 0;
}
