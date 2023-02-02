#include <bit/stdc++.h>

using namespace std;

class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);
        for (auto c : s) {
            if (c == '(') {
                st.push(0);
            } else {
                int v = st.top();
                st.pop();
                st.top() += max(2 * v, 1);
            }
        }
        return st.top();
    }
};

int main() {
    Solution solution;
    cout << solution.scoreOfParentheses("((()))") << endl;
    return 0;
}