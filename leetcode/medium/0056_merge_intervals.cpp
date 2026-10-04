// Tags:  self-balancing BST (e.g. red-black tree, AVL)(online), lazy segment tree(online) , divide and conquer(offline), sort(offline), amortized cost (in case of self-balancing BST).

// TODO: lazy segment tree.

// Lazy segment tree solution works because we abuse the fact that range is small, 
//   complexity: O(nlogR), where R is max range. In our constraints case max n is similar to max R. 
// Divide and conquer is worse than self-balancing BST in practice.
// Sort solution is the simplest, the fastest and has the lowest memory usage in practice (STL sort is highly optimized).

class Solution {
private:
    vector<vector<int>> simpleSolution(vector<vector<int>>& intervals) {
        // sort solution
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> result {intervals[0]};
        for (int i=1; i < intervals.size(); i++) {
            if (intervals[i][0] <= result.back()[1]) {
                int e = max(result.back()[1], intervals[i][1]);
                result.back()[1] = e;
            }
            else
                result.push_back(intervals[i]);
        }
        return result;
    }
    vector<vector<int>> selfBalancingBSTSolution(const vector<vector<int>>& intervals) {
        set<pair<int,int>> S; /*
            Ordered set of distinct intervals. The fact they are distinct is invariant.
        */
        for (auto inter: intervals) {
            int b = inter[0], e = inter[1];
            if (S.empty()) {
                S.insert(make_pair(b,e));
            }
            else {
                // begin() != end()
                auto endItr = S.upper_bound(make_pair(b,e));
                while (endItr != S.end() && endItr->first <= e) {endItr++;}
                if (endItr == S.begin()) {
                    // First segment is on the right from (b,e).
                    S.insert(make_pair(b,e)); // It will go to the beginning.
                }
                else {
                    auto previous = prev(endItr);
                    while (previous != S.begin() && previous->second >= b) {
                        e = max(e, previous->second);
                        b = min(b, previous->first);
                        S.erase(previous);
                        previous = prev(endItr);
                    }
                    if (previous->second >= b) {
                        e = max(e, previous->second);
                        b = min(b, previous->first);
                        S.erase(previous);
                    }
                    S.insert(make_pair(b,e));
                }
            }
        }
        vector<vector<int>> result;
        for (auto itr: S) {
            result.push_back({itr.first, itr.second});
        }
        return result;
    }
    void adjust(vector<vector<int>>& T, vector<vector<int>>& result) {
        int minVal = min(T.back()[0], result.back()[0]);
        int maxVal = max(T.back()[1], result.back()[1]);
        result.pop_back();
        T.pop_back();
        result.push_back({minVal, maxVal});
    }
    vector<vector<int>> divideAndConquerSolution(int b, int e, const vector<vector<int>>& intervals) {
        if (b == e) {return {intervals[b]};}
        int mid = (b+e)/2;
        vector<vector<int>> result;
        auto L = divideAndConquerSolution(b, mid, intervals);
        auto R = divideAndConquerSolution(mid+1, e, intervals);
        while (!L.empty() && !R.empty()) {
            if (!result.empty() && result.back()[0] <= L.back()[1])
                adjust(L, result);
            else if (!result.empty() && result.back()[0] <= R.back()[1])
                adjust(R, result);
            else if (L.back()[1] < R.back()[0]) {
                result.push_back(R.back());
                R.pop_back();
            }
            else if (R.back()[1] < L.back()[0]) {
                result.push_back(L.back());
                L.pop_back();
            }
            else {
                int minVal = min(L.back()[0], R.back()[0]);
                int maxVal = max(L.back()[1], R.back()[1]);
                L.pop_back();
                R.pop_back();
                result.push_back({minVal, maxVal});
            }
        }
        if (L.empty() && !R.empty()) {swap(L, R);}
        while (!L.empty()) {
            if (L.back()[1] >= result.back()[0])
                adjust(L, result);
            else {
                result.push_back(L.back());
                L.pop_back();
            }
        }
        reverse(result.begin(), result.end());
        return result; // NRVO
    }

public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        return simpleSolution(intervals);
    }
};