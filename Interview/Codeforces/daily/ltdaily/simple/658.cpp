#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int left=0;
        int n=arr.size();
        int right=n-1;
        while(right-left>=k)            //区间不断缩小直到符合条件
        {
            if(abs(arr[left]-x)>abs(arr[right]-x)) //左边的差值比较大，那就区间左边缩小
                left++;
            else                            //否则区间右边缩小
                right--;
        }
        return vector<int>(arr.begin() + left, arr.begin() + k + left);
    }
};

int main() {
    Solution solution;
    vector<int> nums ={0,0,1,2,3,3,4,7,7,8};
    int x = 3, k = 5;
    solution.findClosestElements(nums, x, k);

    return 0;
}