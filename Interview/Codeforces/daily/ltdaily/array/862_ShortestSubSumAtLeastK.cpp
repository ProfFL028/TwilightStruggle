// leetcode: https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/submissions/
// hard presum
/**
 * 记数组 \textit{nums}nums 的前缀和数组为 \textit{preSumArr}preSumArr，可以根据 \textit{preSumArr}[i]preSumArr[i] = \sum_{j=0}^{i-1}{nums}[j]∑
j=0
i−1
​
 nums[j] 计算得到。对于边界情况，\textit{preSumArr}[0] = 0preSumArr[0]=0。而从数组 \textit{nums}nums 下标 ii 开始长为 mm 的子数组的和就可以根据 \textit{preSumArr}[i+m] - \textit{preSumArr}[i]preSumArr[i+m]−preSumArr[i] 快速计算得到。
题目要求计算 \textit{nums}nums 中，和大于等于 kk 的最短子数组的长度。可以以 \textit{nums}nums 的每一个下标作为候选子数组的起点下标，都计算满足条件的最短子数组的长度，然后再从这些长度中找出最小值即可。
遍历 \textit{preSumArr}preSumArr 数组，访问过的前缀和先暂存在某种集合 qq 中。根据前缀和数组的性质，后访问到的某个前缀和 \textit{preSumArr}[j]preSumArr[j] 减去之前访问到的某个前缀和 \textit{preSumArr}[i]preSumArr[i]（j \gt ij>i）即为 \textit{nums}nums 中某段子数组的和。因此，每次访问到某个前缀和 \textit{preSumArr}[j]preSumArr[j] 时，可以用它尝试减去集合 qq 中所有已经访问过的前缀和。当某个 qq 中的前缀和 \textit{preSumArr}[i]preSumArr[i]，第一次出现 \textit{preSumArr}[j] - \textit{preSumArr}[i] \geq kpreSumArr[j]−preSumArr[i]≥k 时，这个下标 ii 就找到了以它为起点的最短子数组的长度 j-ij−i。此时，可以将它从 qq 中移除，后续即使还有以它为起点的满足条件的子数组，长度也会大于当前的长度。当一个前缀和 \textit{preSumArr}[j]preSumArr[j] 试减完 qq 中的元素时，需要将它也放入 qq 中。将它放入 qq 前， qq 中可能存在比 \textit{preSumArr}[j]preSumArr[j] 大的元素，而这些元素和 \textit{preSumArr}[j]preSumArr[j] 一样，只能作为再后续访问到的某个前缀和 \textit{preSumArr}[h]preSumArr[h] 的减数。而作为减数时，更大的值只会让不等式 \textit{preSumArr}[h] - \textit{preSumArr}[i] \geq kpreSumArr[h]−preSumArr[i]≥k 更难满足。即使都满足，后访问到的值也可以带来更短的长度。 因此，在把 \textit{preSumArr}[j]preSumArr[j] 放入 qq 时，需要将 qq 中大于等于 \textit{preSumArr}[j]preSumArr[j] 的值也都移除。
接下来考虑 qq 的性质。我们会往 qq 中增加和删除元素。每次增加一个元素 \textit{curSum}curSum 前，先根据不等式删除一部分元素（也可能不删），然后再删除 qq 中所有大于等于 \textit{curSum}curSum 的元素，这样每次加进去的元素都会是 qq 中的唯一最大值，使得 qq 中的元素是按照添加顺序严格单调递增的，我们知道单调队列是满足这样的性质的。而这一性质，也可以帮助找到 qq 中所有满足不等式的值。按照添加的顺序从早到晚，即元素的值从小到大来比较是否满足不等式即可。按照这个顺序，一旦有一个元素不满足，qq 中后续的元素也不会满足不等式，即可停止比较。基于此，我们需要一个集合，可以在两端删除元素，在一端添加元素，因此使用双端队列。
在完成代码时，qq 中暂存的元素是 \textit{preSumArr}preSumArr 的下标，对应下标的前缀和严格单调递增。
 */
#include <bit/stdc++.h>

using namespace std;
class Solution {
public:
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long> preSumArr(n + 1);
        for (int i = 0; i < n; i++) {
            preSumArr[i + 1] = preSumArr[i] + nums[i];
        }
        int res = n + 1;
        deque<int> qu;
        for (int i = 0; i <= n; i++) {
            long curSum = preSumArr[i];
            while (!qu.empty() && curSum - preSumArr[qu.front()] >= k) {
                res = min(res, i - qu.front());
                qu.pop_front();
            }
            while (!qu.empty() && preSumArr[qu.back()] >= curSum) {
                qu.pop_back();
            }
            qu.push_back(i);
        }
        return res < n + 1 ? res : -1;
    }
};


int main() {
    Solution solution;


    return 0;
}