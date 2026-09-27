// template <typename T,typename U>                                                   
// std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
//     return {l.first+r.first,l.second+r.second};                                    
// } 

class Solution {
private:
    // pair<int,int> operator+(const pair<int,int>& a, const pair<int,int>& b) {
    //     return make_pair(a.first+b.first, a.second+b.second);
    // }                                                   
    pair<int,int> add(const pair<int,int>& l,const pair<int,int> & r) {   
        return {l.first+r.first,l.second+r.second};                                    
    } 
    bool _dfs(
        pair<int,int> v,
        int id,
        const vector<vector<char>>& board, 
        vector<vector<bool>>& visited, 
        const string& word) 
        {
            auto [i,j] = v;
            if (v.first < 0 || v.second < 0 ||
              v.first >= visited.size() ||
              v.second >= visited[0].size()
            ) {
                return false;
            }
            if (visited[i][j] || word[id] != board[i][j]) {return false;}
            if (id+1 == word.size()) {return true;}

            visited[i][j]=true;
            if (_dfs(add(v, make_pair(-1,0)), id+1, board, visited, word)) {return true;}
            if (_dfs(add(v, make_pair(0,-1)), id+1, board, visited, word)) {return true;}
            if (_dfs(add(v, make_pair(1,0)), id+1, board, visited, word)) {return true;}
            if (_dfs(add(v, make_pair(0,1)), id+1, board, visited, word)) {return true;}
            
            visited[i][j] = false;
            return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int n = board.size(), m = board[0].size();
        vector<bool> temp (m, false);
        vector<vector<bool>> visited (n, temp); // It should be a copy...
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (_dfs(make_pair(i,j), 0, board, visited, word)) {return true;}
            }
        }
        return false;
    }
};
