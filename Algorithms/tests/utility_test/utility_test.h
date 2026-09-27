#ifndef UTILITY_TEST
#define UTILITY_TEST

#include<string>
#include<vector>
#include<string>
#include<stdexcept>

template<typename T>
void printVector(const std::vector<T>& v);

template<typename T>
void test(const std::vector<T>& result, const std::vector<T>& expected, const std::string& testName);

#include "utility_test.tpp"

#endif