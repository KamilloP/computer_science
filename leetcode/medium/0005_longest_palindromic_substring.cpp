class Solution {
public:
    string longestPalindrome(string s) {
        int best = 1;
        int from = 0, to=0;
        if (s.length() >= 2) {
            if (s[0]==s[1]) {
                // cout << s.substr(0, 2) << "\n";
                from=0;
                to=1;
                best=2;
            }
        }
        for (int i = 1; i < s.length()-1; i++) {
            int M = min(i, int(s.length())-i-1);
            for (int j=1; j<=M; j++) {
                if (s[i-j] != s[i+j]) {break;}
                // cout << s.substr(i-j, 2*j+1) << "\n";
                if (2*j+1 > best) {
                    best = 2*j+1;
                    from = i-j;
                    to = i+j;
                }
            }
            if (s[i] == s[i+1]) {
                // cout << s.substr(i, 2) << "\n";
                if (2 > best) {
                    from = i;
                    to = i+1;
                }
                M = min(i, int(s.length())-i-2);
                for (int j=1; j<=M; j++) {
                    if (s[i-j] != s[i+j+1]) {break;}
                    // cout << s.substr(i-j, 2*j+2) << "\n";
                    if (2*j+2 > best) {
                        best=2*j+2;
                        from = i-j;
                        to = i+j+1;
                    }
                }
            }
        }
        return s.substr(from, to-from+1);
    }
};
