class Solution {
private:
    pair<bool, char> _analyzeLetter(char l) {
        switch (l) {
            case '(':
                return make_pair(true, '(');
                break;
            case '{':
                return make_pair(true, '{');
                break;
            case '[':
                return make_pair(true, '[');
                break;
            case ')':
                return make_pair(false, '(');
                break;
            case '}':
                return make_pair(false, '{');
                break;
            case ']':
                return make_pair(false, '[');
                break;
            default:
                throw -1; 
        }
    }
public:
    bool isValid(string s) {
        stack<char> S;
        for (char letter : s) {
            auto [open, equivalent] = _analyzeLetter(letter);
            if (open) {S.push(equivalent);}
            else if (S.empty() || S.top() != equivalent) {return false;}
            else {S.pop();}
        }
        return S.empty();
    }
};
