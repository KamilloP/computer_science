class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int l = INT_MAX;
        string result = "";
        for (auto s : strs) {
            l = min(l, int(s.length()));
        }
        for (int i = 0; i < l; i++) {
            char letter = strs[0][i];
            for (int j = 1; j < strs.size(); j++) {
                if (strs[j][i] != letter) {return result;}
            }
            result += letter;
        }
        return result;
    }
};

