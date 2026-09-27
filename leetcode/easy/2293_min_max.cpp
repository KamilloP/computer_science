class Solution {
public:
    int minMaxGame(vector<int>& nums) {
        // Total memory O(N) (N/2+N/4+...+1 = N-1).
        int N = nums.size();
        if (N == 1) {return nums[0];}
        if (N%2 == 1) {return -1;}
        vector<int> newArray(N/2, 0);
        for (int i=0; i<N/2; i++) {
            if (i%2 == 0) {
                newArray[i] = min(nums[2*i], nums[2*i+1]);
            }
            else {
                newArray[i] = max(nums[2*i], nums[2*i+1]);
            }
        }
        return minMaxGame(newArray);
    }
};