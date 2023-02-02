#include <iostream>
using namespace std;

class Solution {
public:
    string solveEquation(string equation) {
        pair<int, int> left = parseString(equation.substr(0, equation.find("=")));
        pair<int, int> right = parseString(equation.substr(equation.find("=")+1));
        int x = left.first - right.first;
        int y = right.second - left.second;
        if (x == 0 && y == 0) {
            return "Infinite solutions";
        } else if (x == 0 && y != 0) {
            return "No solution";
        } else {
            return "x=" + to_string(y/x);
        }
    }

    pair<int, int> parseString(string formula) {
        int x = 0;
        int v = 0;
        int cur = 0;
        bool neg = false;

        for (int i = 0; i < formula.size(); i++) {
            char c = formula[i];
            if (c >= '0' && c <= '9') {
                cur = cur * 10 + c - '0';
            } else if (c == 'x') {
                if (cur == 0 && !(i > 0 && formula[i-1]=='0')) {
                    cur = 1;
                }
                if (neg) {
                    x -= cur;
                } else {
                    x += cur;
                }
                cur = 0;
            } else if (c == '+') {
                if (!neg) {
                    v += cur;
                } else {
                    v -= cur;
                }
                cur = 0;
                neg = false;
            } else if (c == '-') {
                if (!neg) {
                    v += cur;
                } else {
                    v -= cur;
                }
                neg = true;
                cur = 0;
            }
        }
        if (!neg) {
            v += cur;
        } else {
            v -= cur;
        }

        return make_pair(x, v);
    }
};

int main() {
    string s = "x+5-3+x=6+x-2";
    Solution solution;
    cout << solution.solveEquation(s) << endl;
}