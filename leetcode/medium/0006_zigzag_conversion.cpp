class Solution {
private:
    int _pos(int N, int m, int r, int pos) {
        // pos is counted from 0.
        // We can assume that N >= 3, N - numRows.
        int branch = pos / (2*N-2), remainder = pos % (2*N-2);
        int height = remainder < N ? remainder : N-1-(remainder-N+1);
        int inRow = (height == N-1 || height == 0) ? branch : 2*branch;
        inRow += int(remainder >= N);
        // cout << "\ninRow: "<< inRow; // 0
        int k = r >= N ? N-2 - (r-N+1) : r;
        if (k == N-1) {k--;}
        int l = N-k-2;
        int first = m+1;
        int second = 2*m+1;
        int third = 2*m+ (r >= N ? 2 : 0);
        int before = 0;
        if (height == 0) 
            before = 0;
        else if (height == 1) 
            before = first;
        else if (height <= k+1) 
            before = first + second*(height-1);
        else
            before = first + second*k + third*(height-k-1);
        return before + inRow;
    }
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {return s;}
        // string result = s; // copy!
        string result(s.length(),'$');
        if (numRows == 2) {
            int m = s.length()/2 + (s.length()%2);
            cout << s.length();
            for (int j=0; j<s.length(); j++) {
                if (j%2 == 0) 
                    result[j/2] = s[j];
                else 
                    result[m+j/2]=s[j];
            }
            return result;
        }

        int m = (s.length()-1) / (2*numRows-2), r = (s.length()-1) % (2*numRows-2);
        for (int i=0; i < s.length(); i++) {
            int pos = _pos(numRows, m, r, i);
            result[pos] = s[i];
        }
        return result;
    }
};
