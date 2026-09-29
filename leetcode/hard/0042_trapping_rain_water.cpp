class Solution {
public:
    int trap(vector<int>& height) {
        /* T(n)=O(n), M(n)=O(n).
            We could make stack in place here by keeping variable `size` equal to maxHeight.size()
            and keeping elements of stack in positions 0,..., size. 
            This way we would reduce memory to O(1) additional.
        */
        int n=height.size();
        if (n==1) {return 0;}
        stack<pair<int,int>> maxHeight;
        maxHeight.push(make_pair(height[0], 0)); /*
            Sequence of higher and higher elevations from right to left,
            first - height, second - position.
        */
        int totalWater=0;
        for (int i=1; i<height.size(); i++) {
            while (maxHeight.size() >= 2 && maxHeight.top().first <= height[i]) {
                int prev = maxHeight.top().first;
                maxHeight.pop();
                totalWater += (min(height[i], maxHeight.top().first) - prev)*
                    (i-maxHeight.top().second-1);
            }
            if (height[i] < maxHeight.top().first) {
                maxHeight.push(make_pair(height[i], i));
            }
            else {
                maxHeight.pop();
                maxHeight.push(make_pair(height[i], i));
            }
        }
        return totalWater;
    }
};