class Solution {
private:
    void search(int i, int j, vector<vector<bool>>& achievable, const string& s, const string& p) {
        int S = s.length(), P = p.length();
        if (achievable[i][j]) {return;}
        achievable[i][j]=true;
        if (j < P) {
            if (p[j] == '*') {
                search(i, j+1, achievable, s, p);
                if (i < S) {
                    search(i+1, j, achievable, s, p);
                }
            }
            else if (p[j] == '?' && i < S) {
                search(i+1, j+1, achievable, s, p);
            }
            else if (i < S && s[i] == p[j]) {
                search(i+1, j+1, achievable, s, p);
            }
        }
    }
public:
    bool isMatch(string s, string p) {
        int S = s.length(), P = p.length();
        vector<bool> falseP (P+1, false);
        vector<vector<bool>> achievable(S+1, falseP); // dp
        search(0,0, achievable, s, p);
        return achievable[S][P];
    }
};