class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) {return false;}
        int y = x;
        int val = 0;
        while (y > 0) {
            if (INT_MAX / 10 < val) {return false;}
            val *= 10;
            if (INT_MAX - (y % 10) < val) {return false;}
            val += y % 10;
            y /= 10;
        }
        return x == val;
    }
};
