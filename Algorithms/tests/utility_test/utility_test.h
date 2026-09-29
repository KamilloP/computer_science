#ifndef UTILITY_TEST
#define UTILITY_TEST

#include<string>
#include<vector>
#include<string>
#include<stdexcept>

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

#include "utility_test.tpp"

#endif