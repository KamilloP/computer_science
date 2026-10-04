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

template<typename T>
void printVector(const std::vector<T>& v);

template<typename T>
void printVector2(const std::vector<std::vector<T>>& v);

template<typename T>
void test(
    const std::vector<T>& result, 
    const std::vector<T>& expected, 
    const std::string& testName,
    bool silentPass = true
);

template<typename T>
void test2(
    const std::vector<std::vector<T>>& result, 
    const std::vector<std::vector<T>>& expected, 
    const std::string& testName,
    bool silentPass = true
);


// readVector below uses operator>>. As a result we cannot read empty string from the file.
template<typename T>
std::vector<T> readVector(std::istream& input = std::cin);

// readVector below uses getline. As a result we can read empty string from the file.
std::vector<std::string> readVectorStringGetline(std::istream& input = std::cin);

template<typename T>
std::vector<std::vector<T>> readVector2(std::istream& input = std::cin);

std::vector<std::vector<std::string>> readVector2StringGetline(std::istream& input = std::cin);

Graph readUndirectedGraph(bool tree=false, std::istream& input = std::cin);

Graph readDirectedGraph(std::istream& input = std::cin);

Graph readTree(std::istream& input = std::cin);

std::tuple<std::string, int, bool> analyzeMainArguments(int argc, char* argv[]);

#include "utility_test.tpp"

#endif