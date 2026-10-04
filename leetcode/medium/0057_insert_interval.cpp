class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> result;
        int b = newInterval[0], e = newInterval[1];
        int i=0;
        while (i < intervals.size() && e >= intervals[i][0]) {
            if (intervals[i][1] < b)
                result.push_back(intervals[i]);
            else {
                // Overlapping
                b = min(b, intervals[i][0]);
                e = max(e, intervals[i][1]);
            }
            i++;
        }
        result.push_back({b,e});
        while (i < intervals.size()) {
            result.push_back(intervals[i]);
            i++;
        }
        return result;
    }
};