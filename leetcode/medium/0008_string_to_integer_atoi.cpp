class Solution {
public:
    int myAtoi(string s) {
        int sign=1;
        int i = 0;
        while (i < s.length() && s[i]==' ') {i++;}
        if (i == s.length()) {return 0;}
        if (s[i] == '-') {
            sign = -1;
            i++;
        }
        else if (s[i] == '+') {i++;}
        if (i == s.length() || s[i] < '0' || s[i] > '9') {return 0;}
        int val = 0; // We treat as negative numbers below.
        while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
            int digit = -int(s[i]-'0');
            if (INT_MIN / 10 > val) {
                val = INT_MIN;
                break;
            }
            val *= 10;
            if (INT_MIN - digit > val) {
                val = INT_MIN;
                break;
            }
            val += digit;
            i++;
        }
        if (sign == 1) {
            if (val == INT_MIN) {
                val = INT_MAX;
            }
            else {
                val *= -1;
            }
        }
        return val;
    }
};
