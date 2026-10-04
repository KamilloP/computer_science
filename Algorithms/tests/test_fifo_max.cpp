#include <bits/stdc++.h>
// #include <stdexcept> // Not included because in bits/stdc++.h
#include "utility_test/utility_test.h"
#include "../fifo_max/fifo_max.h"

// g++ -std=c++17 -Wall -Wextra -pedantic test_fifo_max.cpp -o bin/test_fifo_max

using namespace std;

template<typename T, typename F = decltype(readVector<T>)>
tuple<vector<T>, int, vector<T>> readData(const string& testName, int n, F funcReadVector = readVector<T>) {
    ifstream input_file("dataset/fifo_max/" + testName + "/" + to_string(n) + ".in");
    ifstream expected_file("dataset/fifo_max/" + testName + "/" + to_string(n) + ".out");

    if (!input_file) {
        throw invalid_argument("No such file as `dataset/fifo_max/" + testName + "/" + to_string(n) + ".in`");
    }
    if (!expected_file) {
        throw invalid_argument("No such file as `dataset/fifo_max/" + testName + "/" + to_string(n) + ".out`");
    }
    auto arr = funcReadVector(input_file);
    int k;
    try {
        input_file >> k;
    }
    catch (invalid_argument& e) {
        cerr << "Invalid argument, failed to read int:" << e.what() << "\n";
        throw e;
    }
    auto expected = funcReadVector(expected_file);
    return tuple(arr, k, expected);
}

template<typename T, typename Comp = less<T>>
vector<T> slidingWindow(const vector<T>& arr, int k, Comp comp = Comp{}) {
    int N=arr.size();
    if (k>N) {throw invalid_argument("k > arr.size()!");}
    FifoMax<T, Comp> fm{comp};
    vector<T> result;
    for (int i=0; i<k; i++) {fm.push(arr[i]);}
    result.push_back(fm.max());
    for (int j=k; j<int(arr.size()); j++) {
        fm.push(arr[j]);
        fm.pop();
        result.push_back(fm.max());
    }
    return result;
}

void testSlidingWindow(const vector<int>& arr, int k, const vector<int>& expected, const string& testName, bool silentPass) {
    vector<int> result = slidingWindow(arr, k);
    test(result, expected, testName, silentPass);
}

void testSlidingWindowMin(const vector<int>& arr, int k, const vector<int>& expected, const string& testName, bool silentPass) {
    struct MyComparator {
        bool operator()(int a, int b) {
            return a > b;
        }
    };
    vector<int> result = slidingWindow(arr, k, MyComparator{});
    test(result, expected, testName, silentPass);
}

void testSlidingWindowMinString(const vector<string>& arr, int k, const vector<string>& expected, const string& testName, bool silentPass) {
    struct MyComparator {
        bool operator()(string a, string b) {
            return a > b;
        }
    };
    vector<string> result = slidingWindow(arr, k, MyComparator{});
    test(result, expected, testName, silentPass);
}

int main (int argc, char* argv[]) {
    auto [testName, n, silentPass] = analyzeMainArguments(argc, argv);
    vector<string> possibleTests {"MAX_INT", "MIN_INT", "MIN_STRING"};
    if (find(possibleTests.begin(), possibleTests.end(), testName) == possibleTests.end()) {
        throw invalid_argument("Test name (" + testName +") is not supported");
    }

    if (testName == "MAX_INT") {
        auto [arr, k, expected] = readData<int>(testName, n);
        testSlidingWindow(arr, k, expected, "MAX_INT", silentPass);
    }
    else if (testName == "MIN_INT") {
        auto [arr, k, expected] = readData<int>(testName, n);
        testSlidingWindowMin(arr, k, expected, "MIN_INT", silentPass);
    }
    else {
        auto [arr, k, expected] = readData<string>(testName, n, readVectorStringGetline);
        testSlidingWindowMinString(arr, k, expected, "MIN_STRING", silentPass); 
        // Unfortunately currently we cannot read empty string, as `cin >>` omits whitespace characters.
    }
    // testSlidingWindow({1,3,-1,-3,5,3,6,7}, 3, {3,3,5,5,6,7}, "MAX_INT");
    // testSlidingWindowMin({1,3,-1,-3,5,3,6,7}, 3, {-1,-3,-3,-3,3,3}, "MIN_INT");
    // testSlidingWindowMinString({"aa", "a", "b", "ba", "ac", ""}, 3, {"a", "a", "ac", ""}, "MIN_STRING");
    return 0;
}