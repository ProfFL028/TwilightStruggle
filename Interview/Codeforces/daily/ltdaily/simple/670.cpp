// 
#include  <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int maximumSwap(int num) {
        vector<int> digits;
        while (num) {
            digits.push_back(num % 10);
            num /= 10;
        }
        int n = digits.size();
        int ans = 0;
        for(int i = n-1; i >= 0; i--) {
            auto mx = findMax(digits, i);
            if (mx.first > digits[i]) {
                swap(digits[i], digits[mx.second]);
                break;
            }
        }

        for (auto d : digits) {
            ans = ans * 10 + d;
        }
        return ans;
    }

    pair<int, int> findMax(vector<int>& nums, int last) {
        int mx = nums[0];
        int k = 0;
        for (int i = 1; i < last; i++) {
            if (nums[i] > mx) {
                mx = nums[i];
                k=i;
            }
        }
        return make_pair(mx, k);
    }
};
int main() {
    Solution solution;
    cout << solution.maximumSwap(2736);
    return 0;
}