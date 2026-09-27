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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // I assume that we reuse already existing nodes.
        ListNode* head = new ListNode();
        ListNode* tail = head;

        while (list1 && list2) {
            if (list1->val >= list2->val) {
                swap(list1, list2);
            }
            tail->next = list1;
            tail = tail->next;
            list1 = list1->next;
        }
        if (!list1) {swap(list1, list2);}
        if (list1) {tail->next=list1;}
        tail = head;
        head = head->next;
        delete tail;
        return head;
    }
};
