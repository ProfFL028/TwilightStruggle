// https://leetcode.cn/problems/split-array-with-same-average/

#include <bits/stdc++.h>

using namespace std;

constexpr int N = 10000*29;//10000*30*30;
bitset<N*2+1> cache;
class Solution {
public:
    bool splitArraySameAverage(vector<int> &nums) {
        int n = nums.size(), sum = reduce(nums.begin(), nums.end(), 0);
        for(int& x: nums) x = x * n - sum;
        if (n <= n / gcd(sum, n)) return false;
        cache.reset();
        nums.pop_back();
        for(int x: nums){
            cache |= x > 0 ? (cache << x) : (cache >> -x);
            cache.set(x+N);
            if(cache.test(N)) return true;
        }
        return false;
    }
};

int main() {
    Solution solution;
    return 0;
}
