#include <iostream>
#include <vector>

using namespace std;
/*class Solution {
public:
    bool validPartition(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<bool> ok(nums.size() + 1, false);
        ok[0] = true;
        ok[2] = nums[0] == nums[1];
        for (int i = 2; i < nums.size(); i++) {
            ok[i+1] = (ok[i-1] && (nums[i] == nums[i-1])) ||
                    (ok[i-2] && (nums[i] == nums[i-1] && nums[i] == nums[i-2])) ||
                    (ok[i-2] && (nums[i] - nums[i-1] == 1 && nums[i-1] - nums[i-2] == 1));
        }
        return ok[n];
    }
};*/

class Solution {
public:
    string shiftingLetters(string s, vector<vector<int>>& shifts) {
        vector<int> op(s.size(), 0);
        for(auto& sft: shifts) {
            for (int i = sft[0]; i <= sft[1]; i++) {
                if (sft[2] == 0) {
                    op[i]--;
                } else {
                    op[i]++;
                }
            }
        }
        string ans = s;
        for (int i = 0; i < s.size(); i++) {
            int x = op[i] % 26;
            if (x !=0) {
                int c = ans[i] + x;
                if (c < 'a') {
                    c += 26;
                } else if (c >'z') {
                    c -= 26;
                }
                ans[i] = c;
            }
        }
        return ans;
    }
};
int main() {
    Solution solution;
    vector<vector<int>> v{{4,9,1},{2,5,1},{7,9,0},{6,10,0},{1,7,1},{0,7,1},{0,3,0},{3,3,1},{7,9,0},{7,7,0},{6,7,0},{7,9,0},{3,9,0},{10,10,1},{8,9,0},{6,9,1},{1,2,1},{3,9,0},{8,10,1},{4,7,1},{9,10,1},{8,9,0},{5,8,0},{8,9,1},{0,7,1},{2,2,1},{8,8,1},{3,7,0},{1,10,1},{9,9,1},{4,9,0},{5,6,1},{7,8,1},{8,9,0},{7,7,1},{9,9,1}};
    string s ="ksztajnymer";
    cout << solution.shiftingLetters(s, v) << endl;

}
