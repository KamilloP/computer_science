class Solution {
public:
    string intToRoman(int num) {
        string result = "";
        unordered_map<int, char> um = {
            {1, 'I'}, {5, 'V'}, {10, 'X'},
            {50, 'L'}, {100, 'C'}, {500, 'D'}, 
            {1000, 'M'}
        };
        while (num >= 1000) {
            num -= 1000;
            result += um[1000];
        }
        int div = 100;
        while (div > 0) {
            int nr = num / div;
            num %= div;
            if (nr < 4) {
                for (int i = 0; i < nr; i++) {
                    result += um[div];
                }
            }
            else if (nr == 4) {
                result += string(1, um[div]) + string(1, um[div*5]);
            }
            else if (nr < 9) {
                result += um[div*5];
                for (int i = 0; i < nr-5; i++) {result += um[div];}
            }
            else {
                result += string(1, um[div]) + string(1, um[div*10]);
            }
            // cout << result << " : " << num << " : " << div << " : " << nr << "\n";
            div /= 10;
        }
        return result;
    }
};
