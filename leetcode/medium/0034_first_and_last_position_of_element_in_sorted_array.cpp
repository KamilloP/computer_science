// Tags: binary search
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size() == 0) {return {-1,-1};}
        int l=0, r = nums.size()-1;
        while (l < r) {
            int mid = (l+r)/2;
            if (nums[mid] < target) {l = mid+1;}
            else {r = mid;}
        }
        if (nums[l] != target) {return {-1, -1};}
        int lowerBound = l;
        r = nums.size();
        while (r > l) {
            int mid = (l+r)/2;
            if (nums[mid] <= target) {l = mid + 1;}
            else {r = mid;}
        }
        return {lowerBound, r-1};
    }
};