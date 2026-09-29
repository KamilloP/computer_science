class Solution {
private:
    string removeZerosFromBeginning(string s) {
        int zeros=0;
        int i=0;
        while (i<s.length() && s[i]=='0') {i++;}
        if (i==s.length()) {i--;}
        return s.substr(i, s.length()-i);
    }
    string add(string num1, string num2) {
        num1 = removeZerosFromBeginning(num1);
        num2 = removeZerosFromBeginning(num2);
        if (num1.length() < num2.length()) {
            swap(num1, num2);
        } // Now num1.length() >= num2.length()
        reverse(num1.begin(), num1.end());
        reverse(num2.begin(), num2.end());
        string result="";
        int i=0;
        int val=0;
        while (i < num2.length()) {
            val += int(num1[i]-'0') + int(num2[i]-'0');
            char digit = '0'+char(val%10);
            result += digit;
            val /= 10;
            i++;
        }
        while (i < num1.length()) {
            val += int(num1[i]-'0');
            char digit = '0'+char(val%10);
            result += digit;
            val /= 10;
            i++;
        }
        if (val > 0) {result += '1';}
        reverse(result.begin(), result.end());
        return removeZerosFromBeginning(result);
    }
    string multiplyByDigit(string num1, const int digit) {
        if (digit == 0) {return "0";}
        reverse(num1.begin(), num1.end());
        int val=0;
        string result="";
        for (char d : num1) {
            val += int(d-'0')*digit;
            result += '0'+char(val % 10);
            val /= 10;
        }
        if (val > 0) {
            // It should be <= 8 if `0 <= digit <= 9`.
            result += '0'+char(val);
        }
        reverse(result.begin(), result.end());
        return removeZerosFromBeginning(result);
    }
public:
    string multiply(string num1, string num2) {
        string zeros="", result="0";
        for (int i=num2.size()-1; i>-1; i--) {
            string current = multiplyByDigit(num1, int(num2[i]-'0')) + zeros;
            zeros += "0";
            result = add(result, current);
        }
        return result;
    }
};