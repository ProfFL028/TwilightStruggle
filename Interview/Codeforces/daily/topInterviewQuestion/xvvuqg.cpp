#include <bit/stdc++.h>

using namespace std;

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        if (nums.size()<=2) return false;
        int min1 = INT_MAX, min2 = INT_MAX;
        for (auto num : nums) {
            if (num <= min1) min1 = num;
            else if (num <= min2) min2 = num;
            else return true;
        }
        return false;
    }
};

int main() {
    Solution solution ;
    vector<int> nums{1,2,3,4,5};
    cout << solution.increasingTriplet() << endl;
    return 0;
}