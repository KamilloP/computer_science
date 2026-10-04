class Solution {
private:
    pair<int,int> posRot90(int i, int j, int n) {
        if (n%2==1) {
            int mid = n/2;
            i -= mid; // b
            j -= mid; // a
            // (a+bi)i = -b+ai
            tie(i,j) = make_pair(j, -i);
            return make_pair(mid+i,mid+j);
        }
        // n%2==0
        // Domain expansion: Odd.
        if (i >= n/2) {i++;}
        if (j >= n/2) {j++;}
        tie(i,j) = posRot90(i,j,n+1);
        if (i >= n/2) {i--;}
        if (j >= n/2) {j--;}
        return make_pair(i,j);
    } 
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i=0; i < n/2; i++) {
            for (int j=i; j < n-i-1; j++) {
                auto current = make_pair(i,j);
                auto next = posRot90(current.first, current.second, n);
                int val = matrix[current.first][current.second];
                for (int k=0; k<4; k++) {
                    swap(val, matrix[next.first][next.second]);
                    current = next;
                    next = posRot90(current.first, current.second, n);
                }
            }
        }
    }
};