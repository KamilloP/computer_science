class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int w1 = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[w1] = nums[i];
                w1++;
            }
        }
        return w1;
    }
};
