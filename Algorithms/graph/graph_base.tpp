// #include "graph_base.h"
// bool isProperTree(const Graph& graph) {
//     const auto& [V, E, edges] = graph; // const reference
//     if (V < 1 || E != V-1) {return false;}
//     std::vector<bool> visited(V, false);
//     auto dfs = [&visited, &edges](auto self, int v) {
//         // &edges does not remove const from original edges.
//         if (visited[v]) {return;}
//         visited[v] = true;
//         for (int u : edges[v]) {self(self, u);}
//     };
//     dfs(dfs, 0);
//     return std::all_of(
//         visited.begin(),
//         visited.end(),
//         [](bool b) {return b;}
//     );
// }

bool _findWalkingPath(
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
        if (_findWalkingPath(u, graph, visited, seq)) {
            seq.push_back(v);
        }
    }
    return true;
}

std::vector<int> findWalkingPath(int root, const Graph& graph) {
    const auto& [V, E, edges] = graph;
    if (root < 0 || root > V) {
        throw std::out_of_range("Root is not proper vertex (" + std::to_string(root) + ")");
    }
    std::vector<bool> visited(V, false);
    std::vector<int> result;
    _findWalkingPath(root, graph, visited, result);
    return result;
}

std::vector<int> findHeight(int root, const Graph& graph) {
    const auto& [V, E, edges] = graph;
    std::vector<int> height(V, std::numeric_limits<int>::max());
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

template<typename T>
Graph weightedGraphToSimpleGraph(const WeightedGraph<T>& wG) {
    auto [V, E, weightedEdges] = wG;
    Edges<int> edges(weightedEdges.size());
    auto func = [](std::vector<std::pair<int,T>> wE) {
        std::vector<int> e(wE.size());
        std::transform(
            wE.begin(),
            wE.end(),
            e.begin(),
            [](std::pair<int, T> bw) {return bw.first;}
        );
        return e;
    };
    std::transform(
        weightedEdges.begin(),
        weightedEdges.end(),
        edges.begin(),
        func
    );
    return std::tuple(V, E, edges);
}

template<typename T>
WeightedGraph<T> simpleGraphToWeightedGraph(const Graph& g) {
    auto [V, E, edges] = g;
    Edges<std::pair<int,T>> weightedEdges(edges.size());
    auto func = [](std::vector<int> e) {
        std::vector<std::pair<int,T>> wE(e.size());
        std::transform(
            e.begin(),
            e.end(),
            wE.begin(),
            [](int b) {return std::make_pair(b, static_cast<T>(1));}
        );
        return wE;
    };
    std::transform(
        edges.begin(),
        edges.end(),
        weightedEdges.begin(),
        func
    );
    return std::tuple(V, E, weightedEdges);
}

template<typename T>
std::tuple<
    WeightedGraph<std::pair<T, int>>,
    std::vector<std::pair<int,int>> 
> addIdentifierForWeightedGraph(const WeightedGraph<T>& wGraph) {
    auto [V,E,edges] = wGraph; // copy
    int counter = 0;
    Edges<std::pair<int, std::pair<T, int>>> extendedEdges;
    std::vector<std::pair<int,int>> edgePos;
    for (int v=0; v<V; v++) {
        std::vector<std::pair<int, std::pair<T, int>>> current;
        for (int pos = 0; pos < edges[v].size(); pos++) {
            auto [u, w] = edges[v][pos];
            current.push_back(std::make_pair(u, std::make_pair(w, counter++)));
            edgePos.push_back(std::make_pair(v, pos));
        }
        extendedEdges.push_back(current);
    }
    return std::make_tuple(std::make_tuple(V,E,extendedEdges), edgePos);
}

template<typename T>
std::vector<std::set<std::pair<int, T>>> edgesSetOfWeightedGraph(const WeightedGraph<T>& wGraph) {
    auto& [V,E,edges] = wGraph;
    std::vector<std::set<std::pair<int, T>>> result;
    for (int v=0; v<V; v++) {
        std::set<std::pair<int, T>> S(edges[v].begin(), edges[v].end());
        result.push_back(S);
    }
    return result;
}

void connectedComponent(int v, const int representant, const Graph& graph, std::vector<int>& visited) {
    auto& [V,E,edges] = graph;
    if (visited[v] != -1) {return;}
    visited[v] = representant;
    for (int u: edges[v]) {
        connectedComponent(u, representant, graph, visited);
    }
}