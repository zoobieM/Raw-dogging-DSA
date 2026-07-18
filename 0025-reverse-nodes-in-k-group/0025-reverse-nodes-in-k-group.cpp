/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* groupPrev = &dummy;

        while (true) {
            // Find the kth node of the current group
            ListNode* kth = groupPrev;

            for (int i = 0; i < k && kth != nullptr; i++) {
                kth = kth->next;
            }

            // Fewer than k nodes remain
            if (kth == nullptr)
                break;

            ListNode* groupNext = kth->next;

            // Reverse the current group
            ListNode* prev = groupNext;
            ListNode* current = groupPrev->next;

            while (current != groupNext) {
                ListNode* nextNode = current->next;
                current->next = prev;
                prev = current;
                current = nextNode;
            }

            // Connect the reversed group
            ListNode* oldGroupStart = groupPrev->next;
            groupPrev->next = kth;
            groupPrev = oldGroupStart;
        }

        return dummy.next;
    }
};