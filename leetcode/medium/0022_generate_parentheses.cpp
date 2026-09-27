class Solution {
private:
    void _generate(int open, int to_use, string current,  vector<string>& result) {
        if (to_use > 0) {
            _generate(open+1, to_use-1, current+'(', result);
        }
        if (open > 0) {
            _generate(open-1, to_use, current+')', result);
        }
        if (to_use == 0 && open == 0) {
            result.push_back(current);
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        _generate(0, n, "", result);
        return result;
    }
};
