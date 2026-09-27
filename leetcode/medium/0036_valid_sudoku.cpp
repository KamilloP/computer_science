class Solution {
    bool _isValidRow(int row, const vector<vector<char>>& board) {
        bool present[9];
        fill_n(present, 9, false);
        for (char letter: board[row]) {
            if (letter == '.') {continue;}
            int val = int(letter-'1');
            if (present[val]) {return false;}
            present[val] = true;
        }
        return true;
    }
    bool _isValidColumn(int column, const vector<vector<char>>& board) {
        bool present[9];
        fill_n(present, 9, false);
        for (int i = 0; i < 9; i++) {
            char letter = board[i][column];
            if (letter == '.') {continue;}
            int val = int(letter-'1');
            if (present[val]) {return false;}
            present[val] = true;
        }
        return true;
    }
    bool _isValidSquare(int l, int d, const vector<vector<char>>& board) {
        bool present[9];
        fill_n(present, 9, false);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char letter = board[l+i][d+j];
                if (letter == '.') {continue;}
                int val = int(letter-'1');
                if (present[val]) {return false;}
                present[val] = true;
            }
        }
        return true;
    }
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            if (!_isValidRow(i, board)) {return false;}
            if (!_isValidColumn(i, board)) {return false;}
            if (!_isValidSquare(3*(i/3), 3*(i%3), board)) {return false;}
        }
        return true;
    }
};