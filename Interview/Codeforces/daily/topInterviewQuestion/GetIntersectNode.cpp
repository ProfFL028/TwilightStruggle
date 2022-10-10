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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (headA == nullptr || headB == nullptr)
            return nullptr;

        int lenA = 0, lenB = 0;
        ListNode *curA = headA, *curB = headB;
        while (curA->next) {
            lenA++;
            curA = curA->next;
        }
        while (curB->next) {
            lenB++;
            curB = curB->next;
        }
        if (curA == curB) {
            curA = headA, curB = headB;
            while (lenA > lenB) {
                curA = curA->next;
                lenA--;
            }
            while (lenB > lenA) {
                curB = curB-> next;
                lenB--;
            }
            while (curA != curB) {
                curA = curA->next;
                curB = curB->next;
            }
            return curA;
        } else {
            return nullptr;
        }
    }
};

int main() {
    return 0;
}