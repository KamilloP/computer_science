#include <bits/stdc++.h>
// #include <stdexcept> // Not included because in bits/stdc++.h
#include "utility_test/utility_test.h"
#include "../lifo_max/lifo_max.h"

// g++ -std=c++17 -Wall -Wextra -pedantic test_fifo_max.cpp -o bin/test_fifo_max

using namespace std;

template<typename T, typename Comp = less<T>>
vector<T> operationsSequence(const vector<T>& elements, const vector<string> operations, Comp comp = Comp{}) {
    int N=elements.size();
    if (N != static_cast<int>(operations.size())) {throw invalid_argument("operations.size() != elements.size()!");}
    LifoMax<T, Comp> lm{comp};
    vector<T> result;
    for (int j=0; j<N; j++) {
        string val = operations[j];
        if (val == "push")
            lm.push(elements[j]);
        else if (val == "pop")
            lm.pop();
        else if (val == "top")
            result.push_back(lm.top());
        else
            result.push_back(lm.max());
    }
    return result;
}

void testLifo(const vector<int>& elements, const vector<string> operations, const vector<int>& expected, const string& testName) {
    vector<int> result = operationsSequence(elements, operations);
    test(result, expected, testName);
}

void testLifoMin(const vector<int>& elements, const vector<string> operations, const vector<int>& expected, const string& testName) {
    struct MyComparator {
        bool operator()(int a, int b) {
            return a > b;
        }
    };
    vector<int> result = operationsSequence(elements, operations, MyComparator{});
    test(result, expected, testName);
}

void testLifoMinString(const vector<string>& elements, const vector<string> operations, const vector<string>& expected, const string& testName) {
    struct MyComparator {
        bool operator()(string a, string b) {
            return a > b;
        }
    };
    vector<string> result = operationsSequence(elements, operations, MyComparator{});;
    test(result, expected, testName);
}

int main () {
    testLifo({2,0,3,-1,-1,-1,-1}, {"push","push","push","max","pop","top","max"}, {3, 0, 2}, "MAX_INT");
    testLifoMin({-2,0,-3,-1,-1,-1,-1}, {"push","push","push","max","pop","top","max"}, {-3, 0, -2}, "MIN_INT");
    testLifoMinString({"ab","b","aa","","","",""}, {"push","push","push","max","pop","top","max"}, {"aa", "b", "ab"}, "MAX_INT");
    return 0;
}