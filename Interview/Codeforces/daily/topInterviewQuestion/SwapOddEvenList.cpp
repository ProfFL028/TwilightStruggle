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
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
            return head;

        ListNode* oddHead=head, *evenHead = head->next;
        ListNode* oddCur, *evenCur;
        oddCur = oddHead;
        evenCur = evenHead;
        while (evenCur != nullptr && evenCur->next !=nullptr) {
            oddCur->next = evenCur->next;
            evenCur->next = oddCur->next->next;
            oddCur = oddCur->next;
            evenCur = evenCur->next;
        }
        oddCur->next = evenHead;
        return oddHead;
    }
};

int main() {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    Solution solution;
    solution.oddEvenList(head);

    return 0;
}