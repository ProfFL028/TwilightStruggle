#include <bit/stdc++.h>
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        traverse(root, 0, ans);

        return ans;
    }

    void traverse(TreeNode* node, int depth, vector<vector<int>>& ans) {
        if (node == nullptr) {
            return ;
        }

        if (ans.size() <= depth) {
            ans.push_back(vector<int>());
        }
        if (depth % 2) {
            ans[depth].insert(ans[depth].begin(), node->val);
        } else {
            ans[depth].push_back(node->val);
        }

        traverse(node->left, depth+1, ans);
        traverse(node->right, depth+1, ans);
    }
};

int main() {
    return 0;
}