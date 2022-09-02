#include <bits/stdc++.h>
using namespace std;
class Solution {
        public:
        string fractionToDecimal(int numerator, int denominator) {
            string ans;
            map<int, int> remain;
            int d = numerator / denominator;
            ans += to_string(d);
            if (denominator < 0 && ans[0] != '-' && numerator !=0) {
                ans += '-';
            }
            if (numerator < 0) {
                numerator *= -1;
            }
            if (denominator < 0) {
                denominator *= -1;
            }
            int r = numerator % denominator;
            if (r == 0) {
                return ans;
            }
            int i = 0;
            string app = "";
            while (r && remain.count(r) == 0) {
                remain[r] = i++;
                r *= 10;
                app += to_string(r / denominator);
                r %= denominator;
            }
            if (r == 0) {
                return ans + "." + app;
            } else {
                app.insert(remain[r], "(");
                return ans + "." + app + ")";
            }
        }
};

int main() {
    Solution s;
    cout << s.fractionToDecimal(4, 333) << endl;
    cout << s.fractionToDecimal(7, -12) << endl;
    return 0;
}