//  https://leetcode.cn/leetbook/read/top-interview-questions/xajl22/
#include  <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        ans.resize(n, 0);
        idx.resize(n, 0);
        for (int i = 0; i < n; i++)
            idx[i] = i;
        mergeSort(nums, 0, n - 1);

        return ans;
    }

    void mergeSort(vector<int>& nums, int i, int j) {
        if (i == j) {
            return ;
        }

        if (i == j - 1) {
            if (nums[i]>nums[j])
                ans[idx[i]]++;
            else {
                swap(nums[i], nums[j]);
                swap(idx[i], idx[j]);
            }
            return ;
        }
        int mid = i + (j - i) / 2;
        mergeSort(nums, i, mid);
        mergeSort(nums, mid + 1, j);
        vector<int> tmpIdx(idx);
        int ii = i, jj = mid+1;
        vector<int> tmp;
        int k = 0;
        while (ii <= mid && jj <= j) {
            if (nums[ii] <= nums[jj]) {
                tmp.push_back(nums[jj]);
                idx[i+k] = tmpIdx[jj];
                jj++;
            } else {
                tmp.push_back(nums[ii]);
                ans[tmpIdx[ii]] += (j - jj + 1);
                idx[i+k] = tmpIdx[ii];
                ii++;
            }
            k++;
        }
        while (ii <= mid) {
            tmp.push_back(nums[ii]);
            idx[i+k] = tmpIdx[ii];
            ii++, k++;
        }
        while (jj <= j) {
            tmp.push_back(nums[jj]);
            idx[i+k] = tmpIdx[jj];
            jj++, k++;
        }
        for (k = 0; k <= j - i; k++) {
            nums[i+k] = tmp[k];
        }
    }
    vector<int> idx;
    vector<int> ans;
};

class Solution2 {
public:
    int n;
    vector<int> a, tr;
    // 二分寻找x对应的离散化后的值
    int find(int x)
    {
        int l = 0, r = n - 1;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (a[mid] >= x)
                r = mid;
            else
                l = mid + 1;
        }
        return l + 1;    // 映射的下标从1开始
    }
    int lowbit(int x)
    {
        return x & -x;
    }
    // 给下标x的数加v
    void add(int x, int v)
    {
        for (int i = x; i <= n; i += lowbit(i))
            tr[i] += v;
    }
    // 从1到x的前缀和(x是树状数组的下标)
    int sum(int x)
    {
        int res = 0;
        for (int i = x; i; i -= lowbit(i))
            res += tr[i];
        return res;
    }
    vector<int> countSmaller(vector<int>& nums) {
        a = nums;
        n = nums.size();
        tr.resize(n + 1);
        sort(a.begin(), a.end());
        // 去重，映射前将数组中的重复元素去掉
        a.erase(unique(a.begin(), a.end()), a.end());

        vector<int> res(n);
        for (int i = n - 1; i >= 0; i -- )
        {
            int x = find(nums[i]);
            res[i] = sum(x - 1);
            add(x, 1);
        }
        return res;
    }
};

int main() {
    vector<int> nums {1,2,7,8,5};
    Solution solution;
    vector<int> ans = solution.countSmaller(nums);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}