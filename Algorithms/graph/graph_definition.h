#ifndef __GRAPH_DEFINITION_H__
#define __GRAPH_DEFINITION_H__

#include<vector>
#include<utility>
#include<algorithm>

template<typename EdgeEndpoint>
using Edges = std::vector<std::vector<EdgeEndpoint>>;

template<typename EdgeEndpoint>
using GeneralizedGraph = std::tuple<int, int, Edges<EdgeEndpoint>>;/*
    `EdgeEndpoint` should be `int` or `std::pair<int, T>` (for UnweightedGraph and WeighteGraph).
    Interpretation: 
    auto [V, E, edges] = generalizedGraph, where:
    1) V: Number of vertices, vertices have indices 0, ..., V-1,
    2) E: number of edges, 
    3) edges: description of Edges, 
        if (edges[a][i] == {b,w}), it means e_i = (a,b) \in Edges and weight(e) = w (for weighted graph),
        if (edges[a][i] == b), it means e_i =(a,b) \in Edges (for unweighted graph).
*/

using Graph = GeneralizedGraph<int>;

template<typename T = int>
using WeightedGraph = GeneralizedGraph<std::pair<int, T>>;

bool isProperTree(const Graph& graph);

#include "graph_definition.tpp"

#endif
