class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> positions; /*
            We assume that '(' increases value by 1 and ')' decreases by one. We compute
            cumulative sum over this value, starting from 0.
            `positions` contains last correct position for given accumulated sum, more precisely
            'i'th element correspond for sum i+1. If value would go negative, then we skip element.
            In particlar the element at index 0 corresponds to 1 opening bracket character. Correct position means up to this point this starting position may end with a proper parentheses.
        */
        // Another solution: O(nlogn) with segment tree or ordered set, but this one is O(n).
        int cumulativeSum=0, best = 0;
        for (int i=0; i < int(s.length()); i++) {
            if (s[i] == '(') {
                if (cumulativeSum == positions.size()) {positions.push(i);}
                cumulativeSum++;
            }
            else if (!positions.empty()) {
                if (cumulativeSum == positions.size()) {
                    best = max(best, i-positions.top()+1);
                    cumulativeSum--;
                }
                else {
                    positions.pop();
                    if (!positions.empty()) {
                        best = max(best, i-positions.top()+1);
                        cumulativeSum--;
                    }
                }
            }
        }
        return best;
    }
};