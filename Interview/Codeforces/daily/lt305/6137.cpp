#include <bits/stdc++.h>

using namespace std;
class Solution {
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
};
int main() {
    vector<int> vec = {783377,783378,783379,783380,783381,783382,783383,783384,783385,783386,783387,783388,14925,14925,14925,190887,190887,190887,444668,444668,444668,444668,444669,444670,444671,444672,444673,444674};
    Solution solution;
    cout << solution.validPartition(vec)<< endl;
    string s("51:start:512");
    cout << atoi(s.substr(0, s.find(':')).c_str()) << endl;
    cout << atoi(s.substr(s.find(':', s.find(':')+1)+1).c_str()) << endl;
    stack<int> stk;
}
