class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 1) {return nums[0] == target ? 0 : -1;}
        // Find position of least element.
        int l=0, r = nums.size()-1;
        if (nums[l] > nums[r]) {
            while (r > l) {
                int mid = (l+r)/2;
                if (nums[mid] >= nums[0]) {l = mid+1;}
                else {r = mid;}
            }
            if (target >= nums[0]) {
                l = 0;
                r--;
            }
            else {
                r = nums.size()-1;
            }
        }
        while (r > l) {
            int mid = (l+r)/2;
            if (nums[mid] < target) {l=mid+1;}
            else {r=mid;}
        }
        return nums[l] == target ? l : -1;
    }
};