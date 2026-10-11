// #include "graph.h"

template <typename T, typename HeapElement = std::tuple<T, int, int, int>>
void _primExtendVertex(
    int v, // vertex to extend
    const WeightedGraph<std::tuple<T, int>>& wGraph,
    const std::vector<bool>& inSpanningTree,
    FibonacciHeap<HeapElement>& H,
    std::vector<DoublyLinkedNode<HeapElement>*>& nodes
) {
    auto& [V,E,edges] = wGraph;
    for (auto [u, w, i] : edges[v]) {
        if (!inSpanningTree[u]) {
            if (!nodes[u])
                nodes[u] = H.insert(std::make_tuple(w, v, u, i));
            else if (w < std::get<0>(nodes[u]->val))
                H.decreaseKey(nodes[u], std::make_tuple(w, v, u, i));
        }
    }
}

template <typename T>
std::tuple<
    T, // Total spanning cost
    std::vector<std::pair<int,int>>, // (v,u), this edge comes from v to u
    std::vector<std::tuple<T,int>> // (w,i) - w is weight of edge (v,u), i is identifier of the edge. 
> prim(int root, const WeightedGraph<std::tuple<T, int>>& wGraph, T MAX_VALUE) {
    auto& [V,E,edges] = wGraph;
    if (root < 0 || root >= V)
        throw std::invalid_argument("Root out of range(root=" + std::to_string(root) + ", V=" + std::to_string(V) +")!");
    using HeapElement = std::tuple<T, int, int, int>; // (w, v, u, i)
    FibonacciHeap<HeapElement> H;
    std::vector<std::pair<int,int>> fromTo;
    fromTo.reserve(V-1);
    std::vector<std::tuple<T,int>> edgeInfo;
    edgeInfo.reserve(V-1);
    std::vector<bool> inSpanningTree (V, false);
    inSpanningTree[root] = true;
    std::vector<DoublyLinkedNode<HeapElement>*> nodes (V, nullptr);
    _primExtendVertex(root, wGraph, inSpanningTree, H, nodes);
    T totalCost = static_cast<T>(0);
    while (!H.empty()) {
        auto [w,v,u,i] = H.minVal();
        H.deleteMin();
        nodes[v] = nullptr;
        fromTo.push_back(std::make_pair(v,u));
        edgeInfo.push_back(std::make_tuple(w,i));
        inSpanningTree[u] = true;
        totalCost += w;
        _primExtendVertex(u, wGraph, inSpanningTree, H, nodes);
    }
    return std::make_tuple(totalCost, fromTo, edgeInfo);
}
