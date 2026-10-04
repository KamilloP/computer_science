// Tags: greedy, divide and conquer.

// Time complexity for both solutions is O(n), 
// divide and conquer has 2*n-1 calls of `solution` and more operations per call.
// Memory complexity is O(1) in greedy and O(logn) in divide and conquer.
// Greedy better and easier.
class Solution {
private:
    tuple<int, int, int, int> solution(int b, int e, const vector<int>& nums) {
        // Arguments: b - beginning of segment, e - end of the segment.
        // return: bestSum, sum of segment, max suffix, max prefix
        if (b == e)
            return make_tuple(nums[b], nums[b], nums[b], nums[b]);
        int mid = (b+e)/2;
        auto [bestL, sumL, sufL, preL] = solution(b, mid, nums);
        auto [bestR, sumR, sufR, preR] = solution(mid+1, e, nums);
        return make_tuple(
            max({bestL, bestR, sufL+preR}),
            sumL+sumR,
            max(sufR, sumR+sufL),
            max(preL, sumL+preR)
        );
    }
public:
    int maxSubArray(vector<int>& nums) {
        // Greedy:
        // int best=INT_MIN, biggestEnding=INT_MIN;
        // for (int nr: nums) {
        //     biggestEnding = biggestEnding > 0 ? biggestEnding+nr : nr;
        //     best = max(best, biggestEnding);
        // }
        // return best;
        // Divide and conquer:
        auto [best, sum, suf, pre] = solution(0, nums.size()-1, nums);
        return best;
    }
};