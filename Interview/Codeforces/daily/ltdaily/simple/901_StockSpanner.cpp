// leetcode: https://leetcode.cn/problems/online-stock-span/submissions/

#include <bit/stdc++.h>

using namespace std;
class StockSpanner {
public:
    StockSpanner() {
        this->stk.emplace(-1, INT_MAX);
        this->idx = -1;
    }

    int next(int price) {
        idx++;
        while (price >= stk.top().second) {
            stk.pop();
        }
        int ret = idx - stk.top().first;
        stk.emplace(idx, price);
        return ret;
    }

private:
    stack<pair<int, int>> stk;
    int idx;
};


int main() {
    Solution solution;


    return 0;
}