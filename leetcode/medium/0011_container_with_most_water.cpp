class Solution {
private:
    int _maxAreaRightDominant(const vector<int>& height) {
        // We only focus on area, which have water filled to the level of right line.
        // In particular right line is smaller or equal to left line.
        queue<pair<int, int>> Q;
        int h = -1;
        int N = height.size();
        for (int i = 0; i < N; i++) {
            if (height[i] > h) {
                h = height[i];
                Q.push(make_pair(h, i));
            }
        }
        h = -1;
        int best = 0;
        for (int i = N-1; i>-1; i--) {
            if (height[i] > h) {
                h = height[i];
                while (!Q.empty() && Q.front().first < h) {Q.pop();}
                if (Q.empty() || Q.front().second >= i) {break;}
                best = max(best, (i-Q.front().second)*h);
            }
        }
        return best;
    }
public:
    int maxArea(vector<int>& height) {
        int rightDominant = _maxAreaRightDominant(height);
        reverse(height.begin(), height.end());
        int leftDominant = _maxAreaRightDominant(height);
        reverse(height.begin(), height.end());
        return max(rightDominant, leftDominant);
    }
};
