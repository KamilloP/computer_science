class Solution {
private:
    void backtracking(
        int id,
        vector<int>& current, 
        vector<pair<int, int>>& counter, 
        vector<vector<int>>& result 
    ) {
        if (id == counter.size()) {
            result.push_back(current);
            return;
        }
        if (counter[id].second == 0) {
            backtracking(id+1, current, counter, result);
            return;
        }
        for (int i=id; i < counter.size(); i++) {
            swap(counter[i], counter[id]);
            counter[id].second--;
            current.push_back(counter[id].first);
            backtracking(id, current, counter, result);
            current.pop_back();
            counter[id].second++;
            swap(counter[i], counter[id]);
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int N=nums.size();
        sort(nums.begin(), nums.end()); /* 
            We do not have to use STL sort, but use the fact
            that nums[i] has 21 possible values. However nums.size()<=8,
            which is small. 
        */
        vector<pair<int,int>> counter {make_pair(nums[0], 1)};
        for (int i=1; i<N; i++) {
            if (nums[i-1] != nums[i])
                counter.push_back(make_pair(nums[i], 1));
            else
                counter[counter.size()-1].second++;
        }
        vector<int> current;
        vector<vector<int>> result;
        backtracking(0,current, counter, result);
        return result;
    }
};