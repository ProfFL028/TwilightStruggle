#include <iostream>
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
    TreeNode* trimBST(TreeNode* root, int low, int high) {
        if (root == nullptr) {
            return root;
        }
        TreeNode* cur = root;
        if (root->val > high) {
            cur = trimBST(cur->left, low, high);
        } else if (root->val < low) {
            cur = trimBST(cur->right, low, high);
        } else {
            cur->left = trimBST(cur->left, low, high);
            cur->right = trimBST(cur->right, low, high);
        }

        return cur;
    }
};

int main() {
    auto* node = new TreeNode(3);
    node->left = new TreeNode(1);
    node->right = new TreeNode(4);
    node->left->right = new TreeNode(2);
    Solution solution;
    solution.trimBST(node, 3, 4);


    return 0;
}