#include <bits/stdc++.h>
// #include <stdexcept> // Not included because in bits/stdc++.h
#include "utility_test/utility_test.h"
#include "../rmq/rmq.h"

// g++ -std=c++17 -Wall -Wextra -pedantic test_rmq.cpp -o bin/test_rmq

using namespace std;

template<typename T, typename Comp>
vector<int> minViaRMQ(const vector<T>& arr, const RMQ<T, Comp>& rmq, const vector<pair<int, int>>& queries) {
    vector<int> result;
    for (auto [i,j] : queries) {
        result.push_back(rmq.argmin(i,j, arr));
    }
    return result;
}

template<typename T, typename Comp>
tuple<vector<vector<int>>, vector<int>, vector<int>> getRMQAttributes(
    const RMQ<T, Comp>& rmq
) {
    return {rmq.getRMQ(), rmq.getMSB(), rmq.getPowers2()};
}

template<typename T, typename Comp>
void testRMQTemplate(
    const vector<T>& arr, 
    const RMQ<T, Comp>& RMQ_, 
    const vector<pair<int, int>>& queries, 
    const vector<int>& expected,
    const vector<int>& expectedMSB,
    const vector<int>& expectedPowers2,
    const vector<vector<int>>& expectedRMQ,
    const string& testName
) {
    vector<int> result = minViaRMQ(arr, RMQ_, queries);
    auto [rmq, msb, powers2] = getRMQAttributes(RMQ_);
    test(msb, expectedMSB, testName+":MSB");
    test(powers2, expectedPowers2, testName+":Power2");
    test2(rmq, expectedRMQ, testName+":RMQ");
    test(result, expected, testName+":Queries");
}

void testRMQ(
    const vector<int>& arr, 
    const vector<pair<int, int>>& queries, 
    const vector<int>& expected,
    const vector<int>& expectedMSB,
    const vector<int>& expectedPowers2,
    const vector<vector<int>>& expectedRMQ,
    const string& testName
) {
    int N=arr.size();
    if (N==0) {throw invalid_argument("arr empty!");}
    RMQ<int> rmq(arr);
    testRMQTemplate(arr, rmq, queries, expected, expectedMSB, expectedPowers2, expectedRMQ, testName);
}

void testRMQMax(
    const vector<int>& arr, 
    const vector<pair<int, int>>& queries, 
    const vector<int>& expected,
    const vector<int>& expectedMSB,
    const vector<int>& expectedPowers2,
    const vector<vector<int>>& expectedRMQ,
    const string& testName
) {
     int N=arr.size();
    if (N==0) {throw invalid_argument("arr empty!");}
    struct MyComparator {
        bool operator()(const int a, const int b) const {
            return a > b;
        }
    };
    RMQ<int, MyComparator> rmq(arr);
    testRMQTemplate(arr, rmq, queries, expected, expectedMSB, expectedPowers2, expectedRMQ, testName);
}

void testRMQMaxString(
    const vector<string>& arr, 
    const vector<pair<int, int>>& queries, 
    const vector<int>& expected,
    const vector<int>& expectedMSB,
    const vector<int>& expectedPowers2,
    const vector<vector<int>>& expectedRMQ,
    const string& testName
) {
    struct MyComparator {
        bool operator()(const string& a, const string& b) const {
            return a > b;
        }
    };
    RMQ<string, MyComparator> rmq(arr);
    testRMQTemplate(arr, rmq, queries, expected, expectedMSB, expectedPowers2, expectedRMQ, testName);
}

int main () {
    testRMQ({1,3,-1,-3,5,3,6,7}, {{1,1}, {2,3}}, {1, 3}, {-1, 0, 1, 1, 2, 2, 2, 2, 3}, {1,2,4,8}, {
        {0, 1, 2, 3, 4, 5, 6, 7}, {0, 2, 3, 3, 5, 5, 6}, {3, 3, 3, 3, 5}, {3}
        }, "MIN_INT"
    );
    testRMQMax({1,3,-1,-3,5,3,6,7}, {{1,1}, {2,3}}, {1,2}, {-1,0,1,1,2,2,2,2,3}, {1,2,4,8},{
        {0, 1, 2, 3, 4, 5, 6, 7}, {1, 1, 2, 4, 4, 6, 7}, {1, 4, 4, 6, 7}, {7}
        }, "MAX_INT"
    );
    testRMQMaxString({"aa", "a", "b", "ba", "ac", ""}, {{1,1}, {2,3}}, {1, 3}, {-1,0,1,1,2,2,2}, {1,2,4}, {
        {0, 1, 2, 3, 4, 5}, {0, 2, 3, 3, 4}, {3, 3, 3}
    },  "MAX_STRING");
    return 0;
}