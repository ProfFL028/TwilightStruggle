#include <bit/stdc++.h>
using namespace  std;
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int mx = 0, res = 0;
        for (int i = 0; i < arr.size(); i++) {
            mx = max(mx, arr[i]);
            res += mx == i;
        }
        return res;
    }
};

int main() {
    Solution solution;
    return 0;
}