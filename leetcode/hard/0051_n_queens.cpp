class Solution {
private:
    void solve(vector<int>& current, vector<int>& candidates, vector<vector<int>>& result) {
        int j = current.size();
        if (candidates.empty())
            result.push_back(current);
        for (int k=0; k < candidates.size(); k++) {
            int c = candidates[k];
            int i=0;
            while (i<j && abs(current[i]-c) != j-i) {i++;}
            if (i==j) {
                current.push_back(c);
                swap(candidates[k], candidates[candidates.size()-1]);
                candidates.pop_back();
                solve(current, candidates, result);
                current.pop_back();
                candidates.push_back(c);
                swap(candidates[k], candidates[candidates.size()-1]);
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        // Each solution can be represented by n-permutation P, where P[i] is column index
        // queen in row i is present. Indeed, it is result of pigeonhole principle.
        // Of course not each permutation is proper solution.
        vector<int> current;
        vector<int> candidates;
        vector<vector<int>> permutationResult;
        int i=0;
        while (i<n) {
            candidates.push_back(i);
            i++;
        }
        solve(current, candidates, permutationResult);
        vector<vector<string>> result(permutationResult.size()); // Default value: vector<string>().
        transform(
            permutationResult.begin(),
            permutationResult.end(),
            result.begin(),
            [n](vector<int> permutation) {
                vector<string> board;
                for (int v: permutation) {
                    string row(n, '.');
                    row[v] = 'Q';
                    board.push_back(row);
                }
                return board;
            }
        );
        return result;
    }
};