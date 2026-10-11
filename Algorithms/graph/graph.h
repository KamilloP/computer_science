
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<string>
#include<vector>
#include<stdexcept>
#include<utility>
#include<algorithm>
#include<queue>
#include<optional>
#include<set>
#include<limits>
#include<functional>
#include<iostream> // Just for debugging, remove later

#include "../rmq/rmq.h"
#include "../fib_heap/fib_heap.h"
#include "graph_definition.h"
#include "../tests/utility_test/utility_test.h" // Just for debugging, remove later

// /*
// DEFINITIONS
// */

// template<typename EdgeEndpoint>
// using Edges = std::vector<std::vector<EdgeEndpoint>>;

// template<typename EdgeEndpoint>
// using GeneralizedGraph = std::tuple<int, int, Edges<EdgeEndpoint>>;/*
//     `EdgeEndpoint` should be `int` or `std::pair<int, T>` (for UnweightedGraph and WeighteGraph).
//     Interpretation: 
//     auto [V, E, edges] = generalizedGraph, where:
//     1) V: Number of vertices, vertices have indices 0, ..., V-1,
//     2) E: number of edges, 
//     3) edges: description of Edges, 
//         if (edges[a][i] == {b,w}), it means e_i = (a,b) \in Edges and weight(e) = w (for weighted graph),
//         if (edges[a][i] == b), it means e_i =(a,b) \in Edges (for unweighted graph).
// */

// using Graph = GeneralizedGraph<int>;

// template<typename T = int>
// using WeightedGraph = GeneralizedGraph<std::pair<int, T>>;

/*
BASIC OPERATIONS
*/

template<typename T = int>
Graph weightedGraphToSimpleGraph(const WeightedGraph<T>& wG);

template <typename T = int>
WeightedGraph<T> simpleGraphToWeightedGraph(const Graph& g);

// bool isProperTree(const Graph& graph); 

std::vector<int> findWalkingPath(int root, const Graph& graph);

std::vector<int> findHeight(int root, const Graph& graph);

void connectedComponent(int v, const int representant, const Graph& graph, std::vector<int>& visited);

template<typename T>
std::vector<std::set<std::pair<int, T>>> edgesSetOfWeightedGraph(const WeightedGraph<T>& wGraph);

/*
Argument: WeightedGraph<T>: [V,E,edges]

Return: [extendedWGraph, edgePos], where
1) extendedGraph = [V,E,extendedEdges]: for each (v, pos) such that edges[v][pos] exists,
    let's say edges[v][pos]=[u,w], extendedEdges[v][pos] = [u, [v,i]],
2) edgePos: [v,pos] = edgePos[i], where edges[v][pos] = [u, [w, i]].
*/
template<typename T>
std::tuple<
    WeightedGraph<std::pair<T, int>>,
    std::vector<std::pair<int,int>> 
> addIdentifierForWeightedGraph(const WeightedGraph<T>& wGraph);

/*
ALGORITHMS
*/

class LCA {
private:
    int bucketSize; // B = bucketSize = 1/2 * logN
    int V;
    std::vector<int> walkingPath; // N=2*V-1
    std::vector<int> height; // V
    std::vector<int> firstOccurence; // V 
    std::vector<std::vector<std::vector<int>>> bruteRMQForRepresentant; /*
        2^{B-1} \approx \sqrt{n} representants, for each of them brute RMQ 
        Each representant has encoding of B-1 bits because starting from relative height `0`
        we increase or decrease height by one (B-1) times. Of course bucket size is B and we 
        compute quadratic RMQ for B^2 quries for given representant. 
    */
    std::vector<int> beginOfBucket; // \ceil{N/B}
    std::vector<unsigned int> representant; // \ceil{N/B}
    std::vector<unsigned int> bucketNr; // N
    std::vector<int> arange; // \ceil{N/B}. It is an arr in rmq, we have to pass it to rmq->argmin.
    
    int computeHeight(int bucket) const;

    struct LCAComparator {
        const LCA* lca;
        LCAComparator(const LCA& lca) : lca(&lca) {}
        bool operator()(int a, int b) const {
            // `a` and `b` are number of buckets
            return lca->computeHeight(a) < lca->computeHeight(b);
        }
    };
    std::optional<RMQ<int, LCAComparator>> rmq;

    ///////////////////////////////////////////////////////////
    // Auxilliary functions ///////////////////////////////////
    ///////////////////////////////////////////////////////////
    std::vector<std::vector<int>> computeQuadraticRMQ(const std::vector<int>& relativeHeights);
    
    void computeBruteForRepresentant(
        int nrOfBitsRemaining,
        std::vector<int>& relativeHeights
    );

    int suffixMin(int pos) const;
    int prefixMin(int pos) const;
    int middleMin(int bucketU, int bucketV) const;

public:
    LCA(int root, const Graph& tree);
    ~LCA() {}
    int lca(int u, int v) const;

    std::vector<int> getWalkingPath() const {return walkingPath;}
    std::vector<int> getHeight() const {return height;}
    std::vector<int> getFirstOccurence() const {return firstOccurence;}
    std::vector<int> getBeginOfBucket() const {return beginOfBucket;}
    std::vector<unsigned int> getRepresentant() const {return representant;}
    std::vector<unsigned int> getBucketNr() const {return bucketNr;}
};

// All 'dijkstra' algorithms return tuple: (previous nodes, distances). T is distance type.
// Important remark: algorithms use static_cast<T>(0), which must be provided by the type.
template <typename T=int>
std::tuple<std::vector<int>, std::vector<T>> dijkstraElogE(int root, const WeightedGraph<T>& wGraph, T MAX_VALUE = std::numeric_limits<T>::max());

template <typename T=int>
std::tuple<std::vector<int>, std::vector<T>> dijkstraElogV(int root, const WeightedGraph<T>& wGraph, T MAX_VALUE = std::numeric_limits<T>::max());

// Uses FibonacciHeap.
template <typename T=int>
std::tuple<std::vector<int>, std::vector<T>> dijkstra(int root, const WeightedGraph<T>& wGraph, T MAX_VALUE = std::numeric_limits<T>::max());

template<typename T, typename Comp = std::equal_to<T>>
void assertProperPathFromSource(
    int root,
    const WeightedGraph<T>& wGraph, 
    const std::vector<int>& previous, 
    const std::vector<T>& distances,
    const Comp equal = Comp{},
    const T MAX_VALUE = std::numeric_limits<T>::max()
);

template <typename T>
std::tuple<
    T, // Total distance
    std::vector<std::pair<int,int>>, // (a,b), this edge comes from a to b
    std::vector<std::tuple<T,int>> // (w,i) - w is weight of edge (a,b), i is identifier of the edge. 
> prim(int root, const WeightedGraph<std::tuple<T, int>>& wGraph, T MAX_VALUE = std::numeric_limits<T>::max());

#include "graph_base.tpp"
#include "lca.tpp"
#include "dijkstra.tpp"
#include "mst.tpp"

#endif