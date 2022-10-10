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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if (l1 == nullptr && l2 == nullptr)
            return nullptr;

        ListNode *ans = new ListNode();
        int extra = 0;
        ListNode *cur = ans;
        while (l1 && l2) {
            int a = l1->val + l2->val + extra;
            cur->val = a % 10;
            extra = a / 10;
            l1 = l1->next;
            l2 = l2->next;
            if (extra > 0 || l1 || l2)
                cur->next = new ListNode();
            cur = cur->next;
        }
        while (l1) {
            int a = l1->val + extra;
            cur->val = a % 10;
            extra = a / 10;
            l1 = l1->next;
            if (extra > 0 || l1)
                cur->next = new ListNode();
            cur = cur->next;
        }
        while (l2) {
            int a = l2->val + extra;
            cur->val = a % 10;
            extra = a / 10;
            l2 = l2->next;
            if (extra > 0 || l2)
                cur->next = new ListNode();
            cur = cur->next;
        }
        if (extra) {
            cur->val = extra;
        }
        return ans;
    }
};

int main() {
    Solution solution;

    return 0;
}