class Solution {
private:
    pair<vector<int>, bool> _remove3AndNoticeIfThreeZeros(const vector<int>& nums) {
        // Assumes that nums is sorted.
        vector<int> v;
        int zeros = 0, last = INT_MIN, nr_of_occurences=0;
        for (auto nr : nums) {
            if (nr == 0) {zeros++;}
            if (nr == last) {nr_of_occurences++;}
            else {
                for (int i = 0; i < min(2, nr_of_occurences); i++) {v.push_back(last);}
                last = nr;
                nr_of_occurences=1;
            }
        }
        for (int i = 0; i < min(2, nr_of_occurences); i++) {v.push_back(last);}
        return make_pair(v, zeros >= 3);
    }
    vector<int> _2SameMatching(const vector<int>& nums, vector<vector<int>>& result) {
        int i = 0, j = nums.size()-1;
        vector<int> v;
        while (i+1 < nums.size()) {
            if (nums[i] == nums[i+1]) {
                while (j >= 0 && 2*nums[i]+nums[j]>0) {j--;}
                if (j >= 0 && 2*nums[i]+nums[j] == 0 && nums[i] != nums[j]) {
                    result.push_back({nums[i], nums[i+1], nums[j]});
                }
                i+=2;
            }
            else {i++;}
        }
        int last = INT_MIN;
        for (auto nr : nums) {
            if(nr != last) {
                v.push_back(nr);
                last = nr;
            }
        }
        return v;
    }
    void _distinctTriplets(const vector<int>& nums, vector<vector<int>>& result) {

        for (int i = 0; i+2 < nums.size(); i++) {
            int j=i+1, k = nums.size()-1;
            // cout << "i,j,k=(" << i << "," << j << "," << k << ")\n";
            while (j < k) {
                // cout << "i,j,k=(" << i << "," << j << "," << k << ")\n";
                while (k > j && nums[i]+nums[j]+nums[k] > 0) {k--;}
                // cout << "i,j,k=(" << i << "," << j << "," << k << ")\n";
                if (k > j && nums[i]+nums[j]+nums[k] == 0) {
                    result.push_back({nums[i], nums[j], nums[k]});
                }
                j++;
            }
        }
    }
    void _printVector(const vector<int>& v) {
        cout << "[";
        for (auto nr : v) {cout << nr << ",";}
        cout << "]\n";
    }
    void _printResult(const vector<vector<int>> result) {
        cout << "[\n";
        for (auto v : result) {
            cout << "; ";
            _printVector(v);
        }
        cout << "]\n";
    }

public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> v = nums; // copy
        bool zeros;

        // cout << "After sort:\n";
        sort(v.begin(), v.end());
        // _printVector(v);
        
        // cout << "After analyzing 3+:\n";
        tie(v, zeros) = _remove3AndNoticeIfThreeZeros(v);
        // alternative if undeclared v and b: 
        // `auto[v,b] = _remove3AndNoticeIfThreeZeros(nums);`
        if (zeros) {result.push_back({0,0,0});}
        // _printVector(v);
        // _printResult(result);
        
        // cout << "After analyzing 2:\n";
        v = _2SameMatching(v, result);
        // _printVector(v);
        // _printResult(result);

        // cout << "After analyzing distinct:\n";
        _distinctTriplets(v, result);
        // _printResult(result);
        return result;
    }
};
