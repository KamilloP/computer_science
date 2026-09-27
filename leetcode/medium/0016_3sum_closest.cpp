class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int best = 1000000;
        for (int i=0; i+2 < nums.size(); i++) {
            int j = i+1, k = int(nums.size())-1;
            while (j<k) {
                while (j < k && nums[i]+nums[j]+nums[k] > target) {k--;}
                if (j<k && abs(nums[i]+nums[j]+nums[k]-target) < abs(best-target)) {
                    best = nums[i]+nums[j]+nums[k];
                }
                if (j < k+1 && k+1 < nums.size() && 
                    abs(nums[i]+nums[j]+nums[k+1]-target) < abs(best-target)) {
                        best = nums[i]+nums[j]+nums[k+1];
                }
                j++;
            }
        }
        return best;
    }
};
