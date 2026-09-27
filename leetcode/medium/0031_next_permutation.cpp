class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n=nums.size();
        if (n <= 1) {return;}
        int i=n-2;
        while (i >= 0 && nums[i] >= nums[i+1]) {i--;}
        if (i == -1) {
            i++;
            while (i < n/2) {
                swap(nums[i], nums[n-i-1]);
                i++;
            }
        }
        else {
            int j=i+1;
            while (j<n && nums[i] < nums[j]) {j++;}
            j--;
            swap(nums[i], nums[j]);
            i++;
            j=n-1;
            while (i<j) {
                swap(nums[i], nums[j]);
                i++;
                j--;
            }
        }
    }
};