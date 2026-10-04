class Solution {
private:
    void _permute(vector<int>& nums, int id, vector<vector<int>>& result) {
        if (id == nums.size()-1) {
            result.push_back(nums); // Copy
        }
        else {
            for (int i=id; i < nums.size(); i++) {
                swap(nums[i], nums[id]);
                _permute(nums, id+1, result);
                swap(nums[i], nums[id]);
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        _permute(nums, 0, result);
        return result;
    }
};