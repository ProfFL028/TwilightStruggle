
#include <iostream>
#include <vector>

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
    TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
        TreeNode *root = new TreeNode();
        recur(root, nums);
        return root;
    }

    void recur(TreeNode *parent, vector<int> &nums) {
        if (nums.size() == 0) {
            return;
        }
        if (nums.size() == 1) {
            parent->val = nums[0];
            return;
        }
        int idx = 0, mx = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > mx) {
                idx = i;
                mx = nums[i];
            }
        }
        vector<int> l, r;
        for (int i = 0; i < idx; i++) {
            l.push_back(nums[i]);
        }
        for (int i = idx + 1; i < nums.size(); i++) {
            r.push_back(nums[i]);
        }
        parent->val = nums[idx];
        if (l.size() > 0) {
            parent->left = new TreeNode();
            recur(parent->left, l);
        }
        if (r.size() > 0) {
            parent->right = new TreeNode();
            recur(parent->right, r);
        }
    }
};

int main() {
    Solution solution;
    vector<int> nums;
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(6);
    nums.push_back(0);
    nums.push_back(5);
    TreeNode *root = solution.constructMaximumBinaryTree(nums);
    cout << root->val << endl;
}