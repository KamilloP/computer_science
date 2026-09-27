class Solution {
private:
    void print_vector_of_pairs(vector<pair<int,int>>& v) {
        for (auto p: v) {
            cout << "(" << p.first << ", " << p.second << ")\n";
        }
    }
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //
        vector<pair<int, int>> s;
        for (int i = 0; i < nums.size(); i++) {
            s.push_back(make_pair(nums[i], i));
        }
        // print_vector_of_pairs(s);
        sort(s.begin(), s.end());
        // print_vector_of_pairs(s);
        int from = 0, to = s.size()-1;
        while (from < to) {
            while (s[from].first + s[to].first > target && to > from) {to--;}
            if (to == from) {
                cout << "Error!";
                return {0,1};
            }
            if (s[from].first + s[to].first == target) {
                return {s[from].second, s[to].second};
            }
            from++;
        }
        return {0,1};
    }
};
