#include <bits/stdc++.h>
// #include <stdexcept> // Not included because in bits/stdc++.h
#include "utility_test/utility_test.h"
#include "../lifo_max/lifo_max.h"

// g++ -std=c++17 -Wall -Wextra -pedantic test_lifo_max.cpp -o bin/test_lifo_max

using namespace std;

template<typename T, typename F = decltype(readVector<T,1>)>
tuple<VectorT<T,1>, VectorT<string,1>, VectorT<T,1>> readData(const string& testName, int n, F funcReadVector = readVector<T,1>) {
    ifstream input_file("dataset/lifo_max/" + testName + "/" + to_string(n) + ".in");
    ifstream expected_file("dataset/lifo_max/" + testName + "/" + to_string(n) + ".out");

    if (!input_file) {
        throw invalid_argument("No such file as `dataset/lifo_max/" + testName + "/" + to_string(n) + ".in`");
    }
    if (!expected_file) {
        throw invalid_argument("No such file as `dataset/lifo_max/" + testName + "/" + to_string(n) + ".out`");
    }
    auto arr = funcReadVector(input_file);
    auto operations = readVector<string,1>(input_file);
    auto expected = funcReadVector(expected_file);
    return tuple(arr, operations, expected);
}

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

void testLifo(const vector<int>& elements, const vector<string> operations, const vector<int>& expected, const string& testName, bool silentPass) {
    vector<int> result = operationsSequence(elements, operations);
    test<int,1>(result, expected, testName, silentPass);
}

void testLifoMin(const vector<int>& elements, const vector<string> operations, const vector<int>& expected, const string& testName, bool silentPass) {
    struct MyComparator {
        bool operator()(int a, int b) {
            return a > b;
        }
    };
    vector<int> result = operationsSequence(elements, operations, MyComparator{});
    test<int,1>(result, expected, testName, silentPass);
}

void testLifoMinString(const vector<string>& elements, const vector<string> operations, const vector<string>& expected, const string& testName, bool silentPass) {
    struct MyComparator {
        bool operator()(string a, string b) {
            return a > b;
        }
    };
    vector<string> result = operationsSequence(elements, operations, MyComparator{});;
    test<string,1>(result, expected, testName, silentPass);
}

int main (int argc, char* argv[]) {
    auto [testName, n, silentPass] = analyzeMainArguments(argc, argv);
    vector<string> possibleTests {"MAX_INT", "MIN_INT", "MIN_STRING"};
    if (find(possibleTests.begin(), possibleTests.end(), testName) == possibleTests.end()) {
        throw invalid_argument("Test name (" + testName +") is not supported");
    }

    if (testName == "MAX_INT") {
        auto [arr, operations, expected] = readData<int>(testName, n);
        testLifo(arr, operations, expected, testName, silentPass);
    }
    else if (testName == "MIN_INT") {
        auto [arr, operations, expected] = readData<int>(testName, n);
        testLifoMin(arr, operations, expected, testName, silentPass);
    }
    else {
        auto [arr, operations, expected] = readData<string>(testName, n, readVectorStringGetline<1>);
        testLifoMinString(arr, operations, expected, testName, silentPass);
    }

    // testLifo({2,0,3,-1,-1,-1,-1}, {"push","push","push","max","pop","top","max"}, {3, 0, 2}, "MAX_INT");
    // testLifoMin({-2,0,-3,-1,-1,-1,-1}, {"push","push","push","max","pop","top","max"}, {-3, 0, -2}, "MIN_INT");
    // testLifoMinString({"ab","b","aa","","","",""}, {"push","push","push","max","pop","top","max"}, {"aa", "b", "ab"}, "MIN_STRING");
    return 0;
}