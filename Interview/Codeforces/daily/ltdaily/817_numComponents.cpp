#include <bit/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    int numComponents(ListNode* head, vector<int>& nums) {
        unordered_set<int> st;
        for (auto num : nums) {
            st.insert(num);
        }
        int ans = 0;
        bool isPreInSet = false;
        while(head) {
            if (st.find(head->val) != st.end()) {
                if (!isPreInSet) {
                    ans++;
                }
                isPreInSet = true;
            } else {
                isPreInSet = false;
            }
            head = head->next;
        }
        return ans;
    }
};

int main() {
    return 0;
}