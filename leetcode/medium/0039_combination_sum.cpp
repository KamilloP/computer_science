// Tags: backtracking
class Solution {
    void _backtracking(vector<int>& current, int id, int target, const vector<int>& candidates, vector<vector<int>>& result) {
        // TODO
        if (id == candidates.size() || candidates[id] > target) {return;}
        if (candidates[id] == target) {
            current.push_back(candidates[id]);
            result.push_back(current);
            current.pop_back();
        }
        else {
            _backtracking(current, id+1, target, candidates, result);
            current.push_back(candidates[id]);
            _backtracking(current, id, target-candidates[id], candidates, result);
            current.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // Note that candidates are positive, target also.
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        vector<int> empty = {};
        _backtracking(empty, 0, target, candidates, result);
        return result;
    }
};