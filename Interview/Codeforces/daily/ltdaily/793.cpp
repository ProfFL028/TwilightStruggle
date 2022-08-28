#include <iostream>
using namespace std;
class Solution {
public:
    int preimageSizeFZF(int k) {
        unsigned long long mid1 = bs(k);
        unsigned long long mid2 = bs(k+1);
        return (int)(mid2-mid1);
    }

    unsigned long long bs(int k) {
        unsigned long long l = 0, r=10e9;
        unsigned long long mid = l + (r - l) / 2;
        while (l < r) {
            if (numZeros(mid) < k ) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
            mid = l + (r - l) / 2;
        }
        return mid;
    }

    unsigned long long  numZeros(unsigned long long k) {
        unsigned long long  ans = 0;
        while (k / 5) {
            ans += k / 5;
            k /= 5;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int k = 0;
    solution.preimageSizeFZF(k);
}