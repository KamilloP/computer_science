// Tags: connected components

class Solution {
private:
    inline int vertex(int row, int column, int N) {return (row*N)+column;}
    
    inline pair<int,int> vertexToPosition(int v, int N) {return make_pair(v/N, v%N);}
    
    vector<int> neighbours(int v, int N) {
        auto [r,c] = vertexToPosition(v, N);
        vector<int> result;
        if (r > 0)
            result.push_back(vertex(r-1,c,N));
        if (r+1 < N)
            result.push_back(vertex(r+1,c,N));
        if (c > 0)
            result.push_back(vertex(r,c-1,N));
        if (c+1 < N)
            result.push_back(vertex(r,c+1,N));
        return result;
    }
    void dfs(int v, const int root, vector<int>& representant, unordered_map<int, int>& nrV, const vector<vector<int>>& grid) {
        // Finds largest connected component for a given root,
        // `representative` is a root or -1 if grid[r][c] == 0 or not yet visited vertex.
        int N=grid.size();
        auto [r,c] = vertexToPosition(v,N);
        if (representant[v] != -1 || grid[r][c] == 0) {return;}
        representant[v] = root;
        nrV[root]++;
        for (int u : neighbours(v, N))
            dfs(u, root, representant, nrV, grid);
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        int N=grid.size();
        vector<int> representant(N*N, -1);
        unordered_map<int,int> nrOfVertices; // value 0 is default
        for (int i=0; i<N*N; i++)
            dfs(i, i, representant, nrOfVertices, grid);
        int best = 0;
        for (int i=0; i<N*N; i++) {
            auto [r,c] = vertexToPosition(i, N);
            best = max(best, nrOfVertices[i]);
            if (grid[r][c] == 0) {
                vector<int> roots;
                int current = 1;
                for (int u: neighbours(i, N)) {
                    auto [ur, uc] = vertexToPosition(u, N);
                    if (grid[ur][uc] == 1 &&
                      find(roots.begin(), roots.end(), representant[u]) == roots.end()) {
                        roots.push_back(representant[u]);
                        current += nrOfVertices[representant[u]];
                    }
                }
                best = max(current, best);
            }
        }
        return best;
    }
};