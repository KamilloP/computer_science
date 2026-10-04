class Solution {
private:
    int solve(vector<int>& current, vector<int>& candidates) {
        int j = current.size();
        if (candidates.empty())
            return 1;
        int res=0;
        for (int k=0; k < candidates.size(); k++) {
            int c = candidates[k];
            int i=0;
            while (i<j && abs(current[i]-c) != j-i) {i++;}
            if (i==j) {
                current.push_back(c);
                swap(candidates[k], candidates[candidates.size()-1]);
                candidates.pop_back();
                res += solve(current, candidates);
                current.pop_back();
                candidates.push_back(c);
                swap(candidates[k], candidates[candidates.size()-1]);
            }
        }
        return res;
    }
public:
    int totalNQueens(int n) {
        vector<int> current;
        vector<int> candidates;
        int i=0;
        while (i<n) {
            candidates.push_back(i);
            i++;
        }
        return solve(current, candidates);
    }
};