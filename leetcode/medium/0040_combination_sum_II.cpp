// Tags: backtracking
class Solution {
    vector<pair<int,int>> _findCounter(vector<int>& val) {
        sort(val.begin(), val.end());
        int counter=1;
        vector<pair<int,int>> result;
        for (int i=1; i<int(val.size()); i++) {
            if (val[i] == val[i-1]) {counter++;}
            else {
                result.push_back(make_pair(val[i-1], counter));
                counter=1;
            }
        }
        result.push_back(make_pair(val[val.size()-1], counter));
        return result;
    }
    void _backtracking(
        vector<int>& current,
        int id1,
        int id2,
        const vector<pair<int,int>>& counter,
        int target,
        vector<vector<int>>& result
    ) {
        if (id1 == counter.size() || counter[id1].first > target) {return;}
        if (id2 == counter[id1].second) {
            _backtracking(current, id1+1, 0, counter, target, result);
            return;
        }
        if (counter[id1].first == target) {
            current.push_back(counter[id1].first);
            result.push_back(current);
            current.pop_back();
            return;
        }
        _backtracking(current, id1+1, 0, counter, target, result);
        current.push_back(counter[id1].first);
        _backtracking(current, id1, id2+1, counter, target-counter[id1].first, result);
        current.pop_back();
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<pair<int,int>> counter = _findCounter(candidates); 
        vector<vector<int>> result;
        vector<int> empty;
        _backtracking(empty, 0, 0, counter, target, result);
        return result;
    }
};