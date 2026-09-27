class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {return INT_MAX;}
        if (dividend == 0) {return 0;}
        long long result = 0, sign = 1;
        if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)) {sign = -1;}
        if (dividend > 0) {dividend = -dividend;}
        if (divisor > 0) {divisor = -divisor;}
        vector<long long> divisorPower = {divisor}, pow2 = {sign};
        long long last = divisorPower[divisorPower.size()-1], last2 = pow2[pow2.size()-1];
        // cout << "ok1\n";
        // cout << sign << ' ' << dividend << ' ' << divisor << '\n';
        while (divisorPower[divisorPower.size()-1] >= (long long)(dividend)) {
            last = divisorPower[divisorPower.size()-1];
            last2 = pow2[pow2.size()-1];
            last = last+last;
            last2 = last2+last2;
            divisorPower.push_back(last);
            pow2.push_back(last2);
        }
        // cout << "ok2\n";
        while (dividend <= divisor) {
            last = divisorPower[divisorPower.size()-1];
            last2 = pow2[pow2.size()-1];
            // cout << last << ' ' << last2 << ' ' << dividend << '\n';
            if ((long long)(dividend) <= last) {
                result += int(last2);
                dividend -= int(last);
            }
            pow2.pop_back();
            divisorPower.pop_back();
        }
        return result;
    }
};
