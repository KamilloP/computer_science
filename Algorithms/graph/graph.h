
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<string>
#include<vector>
#include<stdexcept>
#include<utility>
#include<algorithm>

using Graph = std::tuple<int, int, std::vector<std::vector<int>>>;

bool isProperTree(const Graph& graph); 

#include "graph.tpp"

#endif