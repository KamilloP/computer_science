bool isProperTree(const Graph& graph) {
    const auto& [V, E, edges] = graph; // const reference
    if (V < 1 || E != V-1) {return false;}
    std::vector<bool> visited(V, false);
    auto dfs = [&visited, &edges](auto self, int v) {
        // &edges does not remove const from original edges.
        if (visited[v]) {return;}
        visited[v] = true;
        for (int u : edges[v]) {self(self, u);}
    };
    dfs(dfs, 0);
    return std::all_of(
        visited.begin(),
        visited.end(),
        [](bool b) {return b;}
    );
}

bool _findIndorder(
    int v,
    const Graph& graph,
    std::vector<bool>& visited,
    std::vector<int>& seq
) {
    // Return true, if first time visited. Otherwise returns false.
    if (visited[v]) {return false;}
    visited[v] = true;
    seq.push_back(v);
    const auto& [V, E, edges] = graph;
    for (int u : edges[v]) {
        if (_findIndorder(u, graph, visited, seq)) {
            seq.push_back(v);
        }
    }
    return true;
}

std::vector<int> findIndorder(int root, const Graph& graph) {
    const auto& [V, E, edges] = graph;
    if (root < 0 || root > V) {
        throw std::out_of_range("Root is not proper vertex (" + std::to_string(root) + ")");
    }
    std::vector<bool> visited(V, false);
    std::vector<int> result;
    _findIndorder(root, graph, visited, result);
    return result;
}

std::vector<int> findHeight(int root, const Graph& graph) {
    const auto& [V, E, edges] = graph;
    std::vector<int> height(V, INT_MAX);
    std::queue<std::pair<int, int>> nodes;
    nodes.push(std::make_pair(root, 0));
    while (!nodes.empty()) {
        auto [v,h] = nodes.front();
        nodes.pop();
        if (height[v] > h) {  // Not visited
            height[v] = h;
            for (int u: edges[v]) {
                nodes.push(std::make_pair(u, h+1));
            }
        }
    }
    return height;
}