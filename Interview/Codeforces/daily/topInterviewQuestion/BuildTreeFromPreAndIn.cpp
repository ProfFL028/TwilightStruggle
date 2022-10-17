// codeforces: https://leetcode.cn/leetbook/read/top-interview-questions-medium/xvix0d/

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        n = preorder.size();
        mid = 0;
        return recursive(preorder, inorder, 0, n);
    }

    TreeNode* recursive(vector<int>& preorder, vector<int>& inorder, int left, int right) {
        TreeNode* node = new TreeNode(preorder[mid]);
        int i = left;
        for(; i < right; i++) {
            if (inorder[i] == preorder[mid]) {
                if (i > left) {
                    mid++;
                    node->left = recursive(preorder, inorder, left, i);
                }
                if(i+1 < right) {
                    mid++;
                    node->right = recursive(preorder, inorder, i+1, right);
                }
                break;
            }
        }
        return node;
    }


    int n, mid;
};

int main() {
    Solution solution;


    return 0;
}