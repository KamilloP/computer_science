class Solution {
public:
    bool canJump(vector<int>& nums) {
        int best = nums[0], i=0;
        while (best+1 < nums.size() && i <= best) {
            best = max(best, i+nums[i]);
            i++;
        }
        return best+1 >= nums.size();
    }
};