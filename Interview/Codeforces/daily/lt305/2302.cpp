
#include <iostream>
#include <vector>

using namespace std;

// 连续子数组
class Solution {
public:
    long long countSubarrays(vector<int> &nums, long long k) {
        long ans = 0L, sum = 0L;
        for (int left = 0, right = 0; right < nums.size(); ++right) {
            sum += nums[right];
            while (sum * (right - left + 1) >= k)
                sum -= nums[left++];
            ans += right - left + 1;
        }
        return ans;

    }

};

int main() {
    Solution solution;
    vector<int> nums{7,6,7,9,1,5,1,4,9,1,10,8,4,1,7,4,2};
    cout << solution.countSubarrays(nums, 65) << endl;
}