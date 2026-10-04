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