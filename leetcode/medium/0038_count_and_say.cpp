class Solution {
public:
    string countAndSay(int n) {
        if (n == 1) {return "1";}
        string previous = countAndSay(n-1), result;
        int from=0, N=previous.length();
        for (int i = 1; i < N; i++) {
            if (previous[i-1] != previous[i]) {
                result += char(int('0') + (i-from));
                result += previous[i-1];
                from = i;
            }
        }
        result += char(int('0') + (N-from));
        result += previous[N-1];
        return result;
    }
};