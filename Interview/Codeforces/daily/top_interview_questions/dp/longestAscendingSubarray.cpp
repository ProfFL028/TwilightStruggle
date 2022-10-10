// 
#include  <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr(n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int l = 0, r = ans;
            while (l < r) {
                int mid = l + (r - l)/2;
                if (arr[mid] < nums[i])
                    l = mid + 1;
                else
                    r = mid;
            }
            arr[l] = nums[i];
            if (l == ans)
                ans++;
        }
        return ans;
    }
};
int main() {
    Solution solution;

    return 0;
}