class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int i=0;
        while (i<nums.size()) {
            if (nums[i] == i+1) {i++;}
            else if (nums[i] > nums.size() || 
                nums[i] <= 0 ||
                nums[nums[i]-1] == nums[i]
            ) {
                swap(nums[i], nums[nums.size()-1]);
                nums.pop_back();
            }
            else {
                swap(nums[i], nums[nums[i]-1]);
            }
        }
        return 1+nums.size();
    }
};