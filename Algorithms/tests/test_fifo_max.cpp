#include <bits/stdc++.h>
// #include <stdexcept> // Not included because in bits/stdc++.h
#include "utility_test/utility_test.h"
#include "../fifo_max/fifo_max.h"

// g++ -std=c++17 -Wall -Wextra -pedantic test_fifo_max.cpp -o bin/test_fifo_max

using namespace std;

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

void testSlidingWindow(const vector<int>& arr, int k, const vector<int>& expected, const string& testName) {
    vector<int> result = slidingWindow(arr, k);
    test(result, expected, testName);
}

void testSlidingWindowMin(const vector<int>& arr, int k, const vector<int>& expected, const string& testName) {
    struct MyComparator {
        bool operator()(int a, int b) {
            return a > b;
        }
    };
    vector<int> result = slidingWindow(arr, k, MyComparator{});
    test(result, expected, testName);
}

void testSlidingWindowMinString(const vector<string>& arr, int k, const vector<string>& expected, const string& testName) {
    struct MyComparator {
        bool operator()(string a, string b) {
            return a > b;
        }
    };
    vector<string> result = slidingWindow(arr, k, MyComparator{});
    test(result, expected, testName);
}

int main () {
    testSlidingWindow({1,3,-1,-3,5,3,6,7}, 3, {3,3,5,5,6,7}, "MAX_INT");
    testSlidingWindowMin({1,3,-1,-3,5,3,6,7}, 3, {-1,-3,-3,-3,3,3}, "MIN_INT");
    testSlidingWindowMinString({"aa", "a", "b", "ba", "ac", ""}, 3, {"a", "a", "ac", ""}, "MIN_STRING");
    return 0;
}