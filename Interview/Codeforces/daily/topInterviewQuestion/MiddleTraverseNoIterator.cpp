#include <bit/stdc++.h>

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
    vector<int> inorderTraversal(TreeNode *root) {
        if (root == nullptr)
            return {};
        stack < TreeNode * > s;
        TreeNode *cur = root;
        while (cur) {
            s.push(cur);
            cur = cur->left;
        }
        vector<int> ans;
        while (!s.empty()) {
            cur = s.top();
            s.pop();
            ans.push_back(cur->val);
            if (cur->right != nullptr) {
                s.push(cur->right);
                cur = cur->right->left;
                while (cur) {
                    s.push(cur);
                    cur = cur->left;
                }
            }
        }

        return ans;
    }
};

int main() {
    return 0;
}