class Solution {
private:
    inline vector<char> _possibleLetters(char digit) {
        if (digit < '7') {
            int x = digit-'2';
            int a = int('a');
            return {char(a+3*x), char(a+3*x+1), char(a+3*x+2)};
        }
        switch (digit) {
            case '7':
                return {'p', 'q', 'r', 's'};
                break;
            case '8':
                return {'t', 'u', 'v'};
                break;
            default:
                return {'w', 'x', 'y', 'z'};
                break;
        }
    }
    void _letterCombinations(string current, int pos, const string& digits, vector<string>& result) {
        if (pos == digits.length()) {
            result.push_back(current);
            return;
        }
        for (auto letter : _possibleLetters(digits[pos])) {
            _letterCombinations(current+letter, pos+1, digits, result);
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        _letterCombinations("", 0, digits, result);
        return result;
    }
};
