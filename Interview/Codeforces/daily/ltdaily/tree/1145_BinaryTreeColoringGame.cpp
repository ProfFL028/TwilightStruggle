// https://leetcode.cn/problems/binary-tree-coloring-game/
// 
#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool btreeWinningMove(TreeNode* root, int n, int x) {
        int leftCount = 0, rightCount = 0;
        function<int(TreeNode*)> dfs = [&](TreeNode* node) {
            if (node == nullptr)
                return 0;
            int ls = dfs(node->left);
            int rs = dfs(node->right);
            if (node->val == x) {
                leftCount = ls;
                rightCount = rs;
            }
        };
        dfs(root);
        return max({leftCount, rightCount, n - 1 - leftCount-rightCount})* 2 > n;
    }
};

int main() {
    Solution solution;

    return 0;
}
