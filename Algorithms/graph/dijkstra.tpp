// #include "dijkstra.h"

template<typename T, typename Comp>
bool edgeExists(std::pair<int, T> element, const std::set<std::pair<int, T>>& neighboursSet, const Comp equal) {
    // `neighboursSet.find(element) == neighboursSet.end()` is not enough - 
    // set has own weak ordering comparator, but we need to use equality comparator.
    auto [u,w] = element; 
    auto itr = neighboursSet.upper_bound(element);
    if (itr != neighboursSet.end() && itr->first == u && equal(itr->second, w)) {return true;}
    if (itr != neighboursSet.begin()) {
        itr--;
        if (itr->first == u && equal(itr->second, w)) {return true;}
    }
    return false;
}

template<typename T, typename Comp>
void checkVertex(
    int v,
    const int V,
    const std::vector<std::set<std::pair<int, T>>> edgesSet, 
    const std::vector<int>& previous, 
    const std::vector<T>& distances,
    std::vector<bool>& checked, 
    std::vector<bool>& visited,
    const Comp& equal
) {
    if (visited[v]) {
        if (checked[v])
            return;
        else {
            throw std::logic_error("There is a cycle in path, starting in vertex" +
                 std::to_string(v) + "!");
        }
    }
    visited[v] = true;
    int prev = previous[v];
    if (prev < 0 || prev >= V) {
        throw std::logic_error("Vertex previous[v] of graph out of range (v=" +
             std::to_string(v)  + ", previous[v]=" + std::to_string(prev) +
             ", V=" + std::to_string(V) + ")!");
    }
    T w = distances[v] - distances[prev];
    if (!edgeExists(std::make_pair(v,w), edgesSet[prev], equal)) {
        throw std::logic_error("There is no such an edge ([previous[v],v,w]=[" +
            std::to_string(prev) + "," + std::to_string(v) + "," + std::to_string(w) + ")!");
    }
    checkVertex(prev, V, edgesSet, previous, distances, checked, visited, equal);
    checked[v] = true;
}

template<typename T, typename Comp>
void assertProperPathFromSource(
    int root,
    const WeightedGraph<T>& wGraph, 
    const std::vector<int>& previous, 
    const std::vector<T>& distances,
    const Comp equal,
    const T MAX_VALUE
) {
    auto& [V,E,edges] = wGraph;

    if (root < 0 || root >= V)
        throw std::invalid_argument("Root of graph out of range (root=" + std::to_string(root)  + ", V=" + std::to_string(V) + ")!");
    if (int(previous.size()) != V)
        throw std::logic_error("Size of previous is not V (previous.size()=" + std::to_string(previous.size())  + ", V=" + std::to_string(V) + ")!");
    if (int(distances.size()) != V)
        throw std::logic_error("Size of distances is not V (distances.size()=" + std::to_string(distances.size())  + ", V=" + std::to_string(V) + ")!");

    std::vector<std::set<std::pair<int, T>>> edgesSet = edgesSetOfWeightedGraph(wGraph); /*
        It could be unordered set, but there is no default hash function.
    */
    std::vector<bool> checked(V, false), visited(V, false);
    {
        std::vector<int> colours(V, -1);
        Graph graph = weightedGraphToSimpleGraph(wGraph);
        connectedComponent(root, root, graph, colours);
        for (int v=0; v<V; v++) {
            if (v == root) {
                if (previous[v] != -1 || !equal(distances[v], static_cast<T>(0))) {
                    throw std::logic_error(
                        std::string("Problem in root (previous[root]=") + std::to_string(previous[root]) + 
                        std::string(", expected=-1; distances[root]=") + std::to_string(distances[root]) + 
                        std::string(", expected=0)"));
                }
                checked[v] = visited[v] = true;
            }
            if (colours[v] == -1) {
                // v != root because colours[root] = root
                if (previous[v] != -1 || !equal(distances[v], MAX_VALUE)) {
                    // printGraph(graph);
                    // printVector<int, 1>(colours);
                    throw std::logic_error(std::string("Problem in vertex excluded from connected ") + 
                        std::string("component of the root (previous[v]=") + std::to_string(previous[v]) + 
                        std::string(", expected=-1; distances[v]=") + std::to_string(distances[v]) + 
                        std::string(", expected=") + std::to_string(MAX_VALUE) +
                        std::string("; v=") + std::to_string(v) + std::string(")!"));
                }
                checked[v] = visited[v] = true;
            }
        }
    }
    for (int v=0; v<V; v++) {
        checkVertex(v, V, edgesSet, previous, distances, checked, visited, equal);
    }
}

template <typename T>
std::tuple<std::vector<int>, std::vector<T>> dijkstraElogE(int root, const WeightedGraph<T>& wGraph, T MAX_VALUE) {
    const auto& [V, E,  edges] = wGraph;
    using QueueElement = std::tuple<T,int,int>;
    std::priority_queue<
        QueueElement, std::vector<QueueElement>, std::greater<QueueElement>
    > Q; // (distance, vertex, previous vertex)
    std::vector<T> dist (V, MAX_VALUE);
    std::vector<int> prev(V, -1);
    Q.push(std::make_tuple(static_cast<T>(0), root, -1));
    while (!Q.empty()) {
        auto [dV, v, prevV] = Q.top();
        Q.pop();
        if (dist[v] == MAX_VALUE) {
            dist[v] = dV;
            prev[v] = prevV;
            for (auto [u, dU] : edges[v]) {
                if (dist[u] == MAX_VALUE) {
                    Q.push(std::make_tuple(dV+dU, u, v));
                }
            }
        }
    }
    return std::make_tuple(prev, dist);
}

template <typename T>
std::tuple<std::vector<int>, std::vector<T>> dijkstraElogV(int root, const WeightedGraph<T>& wGraph, T MAX_VALUE) {
    // E <= V^2, logE <= log(V^2) = 2 logV, but additional memory is V instead of E.
    const auto& [V, E,  edges] = wGraph;
    using SetElement = std::tuple<T,int>;
    std::set<SetElement> S; // (distance, vertex)
    std::vector<T> dist (V, MAX_VALUE);
    std::vector<int> prev(V, -1);
    S.insert(std::make_tuple(static_cast<T>(0), root));
    dist[root] = static_cast<T>(0);
    while (!S.empty()) {
        auto [dV, v] = *S.begin();
        S.erase(S.begin()); // erase by Iterator
        if (dist[v] == dV) {
            // Admit v. dist[v] = dV already. We have to extend v.
            for (auto [u, dU] : edges[v]) {
                if (dist[u] == MAX_VALUE) {
                    dist[u] = dU+dV; // candidate
                    prev[u] = v;
                    S.insert(std::make_tuple(dV+dU, u));
                }
                else if (dist[u] > dV+dU) {
                    S.erase(std::make_tuple(dist[u], u));
                    dist[u] = dU+dV; // candidate
                    prev[u] = v;
                    S.insert(std::make_tuple(dV+dU, u));
                }
            }
        }
    }
    return std::make_tuple(prev, dist);
}

template <typename T>
std::tuple<std::vector<int>, std::vector<T>> dijkstra(int root, const WeightedGraph<T>& wGraph, T MAX_VALUE) {
    // E + VlogV, uses fibonacci_heap.
    const auto& [V, E,  edges] = wGraph;
    using HeapElement = std::tuple<T,int>;
    FibonacciHeap<HeapElement> H; // (distance, vertex)
    std::vector<T> dist (V, MAX_VALUE);
    std::vector<int> prev(V, -1);
    std::vector<DoublyLinkedNode<std::tuple<T, int>>*> nodes (V, nullptr);
    H.insert(std::make_tuple(static_cast<T>(0), root));
    dist[root] = static_cast<T>(0);
    while (!H.empty()) {
        auto [dV, v] = H.minVal();
        // Admit v. dist[v] = dV already. We have to extend v.
        H.deleteMin();
        nodes[v] = nullptr;
        for (auto [u, dU] : edges[v]) {
            if (dist[u] == MAX_VALUE) {
                dist[u] = dU+dV; // candidate
                prev[u] = v;
                nodes[u] = H.insert(std::make_tuple(dV+dU, u));
            }
            else if (dist[u] > dV+dU) {
                H.decreaseKey(nodes[u], std::make_tuple(dU+dV, u));
                dist[u] = dU+dV; // candidate
                prev[u] = v;
            }
        }
    }
    return std::make_tuple(prev, dist);
}