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
private:
    void _reverse(ListNode* predecessor, ListNode* endNode) {
        // Assumptions: k >= 1 and begin: ...->predecessor->n1->...->nk->endNode->...
        // return: ...->predecessor->nk->...->nk->endNode->...
        ListNode* tail = predecessor->next, *n1=predecessor->next, *next=predecessor->next->next;
        while (next != endNode) {
            ListNode* temp = next->next;
            next->next = tail;
            tail = next;
            next = temp;
        }
        n1->next = endNode;
        predecessor->next = tail;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (k==1) {return head;}
        ListNode h;
        h.next = head;
        ListNode* predecessor = &h;
        while (true) {
            int i=0;
            ListNode* endNode=predecessor->next, *n1=predecessor->next;
            while (i<k && endNode) {
                endNode = endNode->next;
                i++;
            }
            if (i == k) {
                _reverse(predecessor, endNode);
                predecessor=n1;
            }
            else {break;}
        }
        return h.next;
    }
};
