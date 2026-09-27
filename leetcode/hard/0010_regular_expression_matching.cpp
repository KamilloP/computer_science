class Solution {
private:
    string _betterPattern(string p) {
        if (p == "") {return "";}
        string better = "";
        int j = -1;
        for (int i = 0; i < p.length()-1; i++) {
            if (p[i] == '.' && p[i+1] == '*') {
                j = i+1;
                while (j+2 <= p.length() && p[j+2] == '*') {j += 2;}
                i = j;
                better += ".*";
            }
            else {
                better += p[i];
            }
        }
        if (j < int(p.length())-1) {
            // without casting above condition is treated as size_t, thus
            // j=-1 is treated as 2^{64} and result is wrong.
            better += p[p.length()-1];
        }
        return better;
    }

    inline bool _match(char s, char p) {
        return p == '.' || p == s;
    }

    // bool _isMatch(string& s, string& p, int posS, int posP) {
    //     if (posP == p.length() && posS == s.length()) {return true;}
    //     if (posP == p.length()) {return false;}
    //     if (posP == p.length()-1 || p[posP+1] != '*') {
    //         return posS < s.length() && _match(s[posS], p[posP]) && _isMatch(s, p, posS+1, posP+1);
    //     }
    //     // posP <= p.length()-2 && begin of p: "?*"
    //     return _isMatch(s, p, posS, posP+2) || 
    //         (posS < s.length() && _match(s[posS], p[posP]) && _isMatch(s, p, posS+1, posP));
    // }
    bool _isMatch(const string& s, const string& p, int posS, int posP, bool* visited, bool* val) {
        int n = s.length()+1, m = p.length()+1;
        if (visited[m*posS+posP]) {return val[m*posS+posP];}
        visited[m*posS+posP] = true;
        if (posP == p.length() && posS == s.length()) {
            val[m*posS+posP] = true;
            return true;
        }
        if (posP == p.length()) {
            val[m*posS+posP] = false;
            return false;
        }
        if (posP == p.length()-1 || p[posP+1] != '*') {
            val[m*posS+posP] = posS < s.length() && _match(s[posS], p[posP]) &&
             _isMatch(s, p, posS+1, posP+1, visited, val);
            return val[m*posS+posP];
        }
        // posP <= p.length()-2 && begin of p: "?*"
        val[m*posS+posP] =_isMatch(s, p, posS, posP+2, visited, val) || 
            (posS < s.length() && _match(s[posS], p[posP]) && _isMatch(s, p, posS+1, posP, visited, val));
        return val[m*posS+posP];
    }
public:
    bool isMatch(string s, string p) {
        // cout << p << "\n";
        p = _betterPattern(p);
        // cout << p << "\n";
        int n = s.length()+1, m = p.length()+1;
        bool* visited = new bool[n*m];
        bool* val = new bool[n*m];
        fill_n(visited, n*m, false); 
        fill_n(val, n*m, false);
        bool result = _isMatch(s, p, 0, 0, visited, val);
        delete[] visited;
        delete[] val;
        return result;
    }
};
