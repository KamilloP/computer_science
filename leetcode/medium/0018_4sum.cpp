class Solution {
private:
    unordered_map<long long, vector<int>> _findSumIndexD(const vector<int>& nums) {
        // We assume nums is sorted.
        unordered_map<long long,  map<int,int>> M;
        // key=num[c]+num[d], 
        // value=map: key=nums[c], value=c. We remember c as large as possible.
        for (int c = 0; c < nums.size(); c++) {
            for (int d=c+1; d < nums.size(); d++) {
                long long val = nums[c]+nums[d];
                M[val][nums[c]] = c;
            }
        }
        unordered_map<long long, vector<int>> result;
        for (auto [k,m]: M) {
            vector<int> v;
            for (auto [val, idx] : m) {
                // Important - it is sorted because nums was sorted and m is ordered map.
                v.push_back(idx);
            }
            result[k] = v;
        }
        return result;
    }
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        set<vector<int>> S;
        unordered_map<long long, vector<int>> M = _findSumIndexD(nums);

        for (int a=0; a+3 < nums.size(); a++) {
            for (int b=a+1; b+2 < nums.size(); b++) {
                long long val = (long long)(target) - (long long)(nums[a]) - (long long)(nums[b]);
                auto indicesC = M[val];
                auto itC = upper_bound(indicesC.begin(), indicesC.end(), b);
                while (itC != indicesC.end()) {
                    vector<int> candidate = {
                        nums[a],
                        nums[b], 
                        nums[*itC],
                        int((long long)(target-nums[a]) - (long long)(nums[b]+nums[*itC]))
                    };
                    S.insert(candidate);
                    itC++;
                }
            }
        }
        vector<vector<int>> result(S.begin(), S.end());
        return result;
    }
};

// // Too slow solution because of repetitions:
// class Solution {
// public:
//     vector<vector<int>> fourSum(vector<int>& nums, int target) {
//         sort(nums.begin(), nums.end());
//         set<vector<int>> S; 
//         // unordered has issue - no hash function. We would need to deafine good hash function.
//         unordered_map<int, vector<pair<int,int>>> M;
//         auto comp = [](pair<int, int> a, pair<int,int> b) {
//             return a.first < b.first || (a.first == b.first && a.second < b.second);
//         };
//         for (int i = 0; i < nums.size(); i++) {
//             for (int j=i+1; j < nums.size(); j++) {
//                 int val = nums[i]+nums[j];
//                 M[nums[i]+nums[j]].push_back(make_pair(i,j));
//             }
//         }
//         // Note that for any key `k` in `M` vector `M[k]` is already sorted 
//         // because of order of indices we analyze.

//         for (int i=0; i+3 < nums.size(); i++) {
//             for (int j=i+1; j+2 < nums.size(); j++) {
//                 auto indices = M[target-nums[i]-nums[j]];
//                 auto it = upper_bound(indices.begin(), indices.end(), make_pair(j+1,-1), comp);
//                 // Probably we do not even need to define comparator, but as a training.
//                 while (it != indices.end()) {
//                     vector<int> candidate = {nums[i], nums[j], nums[it->first], nums[it->second]};
//                     S.insert(candidate);
//                     it++;
//                 }
//             }
//         }
//         vector<vector<int>> result(S.begin(), S.end());
//         return result;
//     }
// };
