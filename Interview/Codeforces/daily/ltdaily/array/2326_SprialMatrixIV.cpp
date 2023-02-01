// https://leetcode.cn/problems/spiral-matrix-iv/
// 
#include <bits/stdc++.h>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}

    ListNode(initializer_list<int> list) {
        if (list.size() > 0) {
            val = *list.begin();
            auto p = list.begin();
            p++;
            ListNode* cur = this;
            while(p != list.end()) {
                cur->next = new ListNode(*p);
                cur = cur->next;
                p++;
            }
        }
    }

    friend ostream& operator<<(ostream& output, ListNode* node) {
        output << "[";
        while (node != nullptr) {
            output << node->val << ", ";
            node = node->next;
        }
        output << "\b\b]";
        return output;
    }
};

class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode *head) {
        vector<vector<int>> ans(m, vector<int>(n, -1));
        int i = 0;
        int dir = 0;
        int row = 0, col = 0;
        int curStep = 0;
        int remainRow = n, remainCol = m;
        while (i < n * m && head != nullptr) {
            ans[row][col] = head->val;
            i++;
            curStep++;
            if (dir == 0) {
                col++;
                if (curStep == remainRow) {
                    curStep = 0;
                    remainCol -= 1;
                    dir = 1;
                    col--;
                    row++;
                }
            } else if (dir == 1) {
                row++;
                if (curStep == remainCol) {
                    curStep = 0;
                    remainRow -= 1;
                    dir = 2;
                    row--;
                    col--;
                }
            } else if (dir == 2) {
                col--;
                if (curStep == remainRow) {
                    curStep = 0;
                    remainCol -= 1;
                    dir = 3;
                    col++;
                    row--;
                }
            } else if (dir == 3) {
                row--;
                if (curStep == remainCol) {
                    curStep = 0;
                    remainRow -= 1;
                    dir = 0;
                    col++;
                    row++;
                }
            }
            head = head->next;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    auto* head = new ListNode{1,2,3,4,5,6,7,8,9,10,11,12};
    auto ans = solution.spiralMatrix(3, 5, head) ;

    cout << "[";
    for (const auto& row : ans) {
        cout << "[";
        for (auto col : row) {
            cout << col << ", ";
        }
        cout << "\b\b]";
    }
    cout << "]";
    return 0;
}
