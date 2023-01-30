// https://leetcode.cn/problems/merge-in-between-linked-lists/
// 
#include <bits/stdc++.h>

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
    /**
     * Move a pointer prevA to [a-1]th node, and move another pointer prevB to bth node.
     * set prevA->next to list2's head. and set list2's last node to prevB.
     * return the head of list1.
     * @param list1
     * @param a
     * @param b
     * @param list2
     * @return
     */
    ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) {
        ListNode* prevA = list1;
        for (int i = 0; i < a - 1; i++) {
            prevA = prevA->next;
        }
        ListNode* prevB = prevA;
        for(int i = 0; i < b - a + 2; i++) {
            prevB = prevB->next;
        }
        prevA->next = list2;
        while (list2->next != nullptr) {
            list2 = list2->next;
        }
        list2->next = prevB;
        return list1;
    }
};

int main() {
    Solution solution;

    return 0;
}
