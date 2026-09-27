class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> um = {
            {'I', 1}, {'V', 5}, 
            {'X', 10}, {'L', 50}, 
            {'C', 100}, {'D', 500},
            {'M', 1000} 
        };
        int last = 1000;
        int result = 0;
        for (int i = 0; i < s.length(); i++) {
            result += um[s[i]];
            if (last < um[s[i]]) {
                result -= 2*last;
            }
            last = um[s[i]];
        }
        return result;
    }
};
