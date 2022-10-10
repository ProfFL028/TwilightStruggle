#include <bit/stdc++.h>
using namespace std;
class Solution {
public:
    bool areAlmostEqual(string s1, string s2) {
        int n = s1.length();
        int a,b;
        int diffCount = 0;
        for (int i = 0; i < n; i++) {
            if (s1[i] != s2[i]) {
                if (diffCount == 0) {
                    a = s1[i];
                    b = s2[i];
                    diffCount++;
                } else if (diffCount == 1) {
                    if (a == s2[i] && b == s1[i]) {
                        diffCount++;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
        return diffCount == 0 || diffCount == 2;
    }
};

int main() {
    return 0;
}