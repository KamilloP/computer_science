#ifndef __UTILITY_TEST_H__
#define __UTILITY_TEST_H__

#include<iostream>
#include<string>
#include<vector>
#include<string>
#include<stdexcept>
#include<utility>
#include<algorithm>
#include "../../graph/graph.h" // alias for `Graph` and function `isProperGraph`

template<typename T, int N>
struct VectorType {
    using type = std::vector<typename VectorType<T, N - 1>::type>;
};

template<typename T>
struct VectorType<T, 0> {
    using type = T;
};

template<typename T, int N>
using VectorT = typename VectorType<T, N>::type;

// readVector below uses operator>>. As a result we cannot read empty string from the file.
template<typename T, int N>
VectorT<T, N> readVector(std::istream& input = std::cin);

// readVector below uses getline. As a result we can read empty string from the file.
template<int N>
VectorT<std::string, N> readVectorStringGetline(std::istream& input = std::cin);

template<typename T, int N>
void printVector(const VectorT<T, N>& v);

template<typename T, int N>
void test(
    const VectorT<T, N> result, 
    const VectorT<T, N>& expected, 
    const std::string& testName, 
    bool silentPass
);

Graph readUndirectedGraph(bool tree=false, std::istream& input = std::cin);

Graph readDirectedGraph(std::istream& input = std::cin);

Graph readTree(std::istream& input = std::cin);

std::tuple<std::string, int, bool> analyzeMainArguments(int argc, char* argv[]);

#include "utility_test.tpp"

#endif