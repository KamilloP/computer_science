// Tags: greedy
class Solution {
public:
    int jump(vector<int>& nums) {
        int N=nums.size(), lastPos=0, nrOfJumps=0, lastAchievable=0;
        if (N==1) {return 0;}
        while (lastPos+nums[lastPos] < N-1) {
            int achievable = lastPos + nums[lastPos];
            int best=-1, newPos=-1;
            for (int i=lastAchievable+1; i<=achievable; i++) {
                if (best < i+nums[i]) {
                    best = i+nums[i];
                    newPos=i;
                }
            }
            lastPos = newPos;
            lastAchievable = achievable;
            nrOfJumps++;
        }
        return nrOfJumps+1;
    }
};