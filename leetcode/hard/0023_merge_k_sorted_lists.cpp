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
    ListNode* _naiveMergeKLists(vector<ListNode*>& lists) {
        // We reuse already existing nodes here.
        ListNode head; // Constructor automatically run.
        // We create new object here, at the end it will be destroyed, 
        // no delete needed.
        ListNode* prev = &head;
        while (!lists.empty()) {
            int min_val = 100000, idx = -1, i=0;
            while (i < lists.size()) {
                if (!lists[i]) {
                    swap(lists[i], lists[lists.size()-1]);
                    lists.pop_back();
                }
                else {
                    if (min_val > lists[i]->val) {
                        min_val = lists[i]->val;
                        idx = i;
                    }
                    i++;
                }
            }
            if (idx != -1) {
                prev->next = lists[idx];
                prev = prev->next;
                lists[idx] = lists[idx]->next;
            }
        }
        return head.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // We reuse already existing nodes here.
        auto comp = [](ListNode* l, ListNode* r) {
            // if (!r && l) {return true;}
            // if (!l) {return false;}
            // Invariant: pq does not have nullptr as element.
            return l->val > r->val;
        };
        priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> pq;
        while (!lists.empty()) {
            ListNode* current = lists[lists.size()-1];
            if (current) {pq.push(current);}
            lists.pop_back();
        }
        ListNode head; // Constructor automatically run.
        // We create new object here, at the end it will be destroyed, 
        // no delete needed.
        ListNode* prev = &head;
        while (!pq.empty()) {
            // Invariant: pq has no nullptr as element.
            ListNode* current = pq.top();
            pq.pop();
            prev->next = current;
            prev = prev->next;
            current = current->next;
            if (current) {
                // We could also just push it, but it last longer.
                pq.push(current);
            }
        }
        return head.next;
    }
};
