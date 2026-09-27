class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int w1=0, last=INT_MIN;
        for(int i=0; i<nums.size();i++) {
            if (last != nums[i]) {
                last = nums[i];
                nums[w1] = last;
                w1++;
            }
        }
        return w1;
    }
};
