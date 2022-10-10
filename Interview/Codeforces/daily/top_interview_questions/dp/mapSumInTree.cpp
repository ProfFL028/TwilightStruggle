//  https://leetcode.cn/leetbook/read/top-interview-questions/x2hnpi/
#include  <bits/stdc++.h>

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
    int maxPathSum(TreeNode *root) {
        dfs(root);
        if (maxNode < 0) {
            return maxNode;
        }
        return ans;
    }

    int dfs(TreeNode *node) {
        maxNode = max(node->val, maxNode);
        int left = 0;
        if (node->left) {
            left = max(left, dfs(node->left));
        }
        int right = 0;
        if (node->right) {
            right = max(right, dfs(node->right));
        }

        ans = max(ans, left);
        ans = max(ans, right);
        ans = max(ans, left + right + node->val);
        // can only have one cross node.
        return max(left + node->val, right + node->val);
    }

    int ans = -100001;
    int maxNode = -100001;
};

int main() {
    Solution solution;

    return 0;
}