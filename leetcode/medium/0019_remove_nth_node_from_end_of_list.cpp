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
    ListNode* _reverse(ListNode* head) {
        // Creates a reversed copy of ListNode
        if (!head) {return nullptr;}
        ListNode* next = new ListNode(head->val);
        head = head->next;
        while (head) {
            next = new ListNode(head->val, next);
            head = head->next;
        }
        return next;
    }
    ListNode* _removeN(ListNode* head, int n) {
        // Removes n node (and deallocate memory) if list has at least n nodes, 
        // otherwise it does not change the list. Returns list.
        if (!head) {return nullptr;}
        head = new ListNode(0, head);
        ListNode* prev = head;
        int k = 1;
        while (k<n && prev->next) {
            prev = prev->next;
            k++;
        }
        if (prev->next) {
            ListNode* temp = prev->next;
            prev->next = prev->next->next;
            delete temp;
        }
        prev = head;
        head = head->next;
        delete prev;
        return head;
    }
    void _delete_list(ListNode* head) {
        if (!head) {return;}
        _delete_list(head->next);
        delete head;
    }

public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        head = _reverse(head); // COPY!
        head = _removeN(head, n);
        ListNode* rev = _reverse(head); // COPY!
        _delete_list(head);
        return rev;
    }
};
