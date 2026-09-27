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
    ListNode* swapPairs(ListNode* head) {
        ListNode h;
        h.next = head;
        ListNode* current = &h;
        while (current->next && current->next->next) {
            ListNode* temp1 = current->next, *temp2 = current->next->next;
            current->next = temp2;
            temp1->next = temp2->next;
            temp2->next = temp1;
            current = current->next->next;
        }
        return h.next;
    }
};
