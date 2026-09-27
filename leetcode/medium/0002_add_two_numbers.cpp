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
    void _print_list(ListNode* l) {
        cout << "[";
        while (l->next) {
            cout << l->val << ", ";
            l = l->next;
        }
        cout << l->val << "]\n";
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* l = new ListNode();
        auto r = l;
        int sum = 0;
        while (l1 && l2) {
            sum += l1->val + l2->val;
            l1 = l1->next;
            l2 = l2->next;
            l->val = sum % 10;
            sum /= 10;
            l->next = new ListNode();
            l = l->next;
        }
        if (l2) {
            l1 = l2;
        }
        while (l1) {
            sum += l1->val;
            l1 = l1->next;
            l->val = sum % 10;
            sum /= 10;
            l->next = new ListNode();
            l = l->next;
        }
        l->val = sum;
        // The only issue is that at the end we might have node with value 0.
        if (r->next) {
            l = r;
            while (l->next->next) {l = l->next;}
            if (l->next->val == 0) {
                delete l->next;
                l->next=nullptr;
            }
        }
        // _print_list(r);
        return r;
    }
};
