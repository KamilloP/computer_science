class Solution {
public:
    int reverse(int x) {
        int sign = x >= 0 ? 1 : -1;
        int val = 0;
        int y = x / 10;
        val += x - y*10;
        val *= -sign; // Now val <= 0.
        x = y;
        x *= -sign; // x <= 0.
        // cout << INT_MIN << "\n";
        while (x < 0) {
            if (INT_MIN / 10 > val) {return 0;}
            val *= 10;
            y = x / 10;
            if (INT_MIN - (x-y*10) > val) {return 0;}
            val += x-y*10;
            x = y;
        }
        if (sign == -1 && val == INT_MIN) {return 0;}
        return sign*(-val);
    }
};
