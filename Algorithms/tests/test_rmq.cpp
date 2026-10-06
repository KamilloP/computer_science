#include <bits/stdc++.h>
// #include <stdexcept> // Not included because in bits/stdc++.h
#include "utility_test/utility_test.h"
#include "../rmq/rmq.h"
#include <argparse/argparse.hpp>

// g++ -std=c++17 -Wall -Wextra -pedantic test_rmq.cpp -o bin/test_rmq

using namespace std;

template<typename T, typename F = decltype(readVector<T,1>)>
tuple<vector<T>, vector<pair<int,int>>> readDataInput(const string& testName, int n, F funcReadVector = readVector<T,1>) {
    ifstream input_file("dataset/rmq/" + testName + "/" + to_string(n) + ".in");
    if (!input_file) {
        throw invalid_argument("No such file as `dataset/rmq/" + testName + "/" + to_string(n) + ".in`");
    }
    auto arr = funcReadVector(input_file);
    vector<pair<int,int>> queries;
    {
        auto first = readVector<int,1>(input_file);
        auto second = readVector<int,1>(input_file);
        if (first.size() != second.size()) {
            throw invalid_argument("First size is different that second size!");
        }
        queries.reserve(first.size());
        for (size_t i=0; i < first.size(); i++) {
            queries.emplace_back(first[i], second[i]);
        }
    }
    return tuple(arr, queries);
}

template<int N>
VectorT<int, N> readDataExpected(const string& testName, const string& taskName, int n) {
    ifstream expected_file("dataset/rmq/" + testName + "/" + taskName + "/" + to_string(n) + ".out");
    if (!expected_file)
        throw invalid_argument("No such file as `dataset/rmq/" + testName + "/" + taskName + "/" + to_string(n) + ".out`");
    return readVector<int,N>(expected_file);
}

// vector<vector<int>> readDataExpected2(const string& testName, const string& taskName, int n) {
//     ifstream expected_file("dataset/rmq/" + testName + "/" + taskName + "/" + to_string(n) + ".out");
//     if (!expected_file)
//         throw invalid_argument("No such file as `dataset/rmq/" + testName + "/" + taskName + "/" + to_string(n) + ".out`");
//     return readVector<int,2>(expected_file);
// }

template<typename T, typename Comp>
vector<int> minViaRMQ(const vector<T>& arr, const RMQ<T, Comp>& rmq, const vector<pair<int, int>>& queries) {
    vector<int> result;
    for (auto [i,j] : queries) {
        result.push_back(rmq.argmin(i,j, arr));
    }
    return result;
}

template<typename T, typename Comp>
vector<int> computeOutput(
    const RMQ<T, Comp>& rmq, 
    const vector<T>& arr, 
    const vector<pair<int,int>>& queries, 
    const string& taskName
) {
    if (taskName == "MSB")
        return rmq.getMSB();
    if (taskName == "Powers2")
        return rmq.getPowers2();
    // Queries
    return minViaRMQ(arr, rmq, queries);
}

template<typename T, typename Comp>
void testRMQTemplate(
    const vector<T>& arr, 
    const RMQ<T, Comp>& rmq, 
    const vector<pair<int, int>>& queries,
    const string& testName,
    const string& taskName,
    int n,
    bool silentPass
) {
    if (taskName != "RMQ") {
        auto expected = readDataExpected<1>(testName, taskName, n);
        auto output = computeOutput(rmq, arr, queries, taskName);
        test<int,1>(output, expected, testName + ":" + taskName, silentPass);
    }
    else {
        auto expected = readDataExpected<2>(testName, taskName, n);
        auto output = rmq.getRMQ();
        test<int,2>(output, expected, testName + ":" + taskName, silentPass);
    }
}

int main (int argc, char* argv[]) {
    argparse::ArgumentParser program("algorithms_tests");
    program.add_argument("testName")
        .help("Name of the test (MAX_INT, MIN_INT or MIN_STRING)");
    program.add_argument("taskName")
        .help("Name of the task (RMQ, Powers2, MSB or Queries)");
    program.add_argument("n")
        .help("Test identifier (number)")
        .scan<'i', int>();
    program.add_argument("--loudPass")
        .help("Whether passed test should be logged or not")
        .default_value(false)
        .implicit_value(true);
    try {
        program.parse_args(argc, argv);    // Example: ./main --color red --color green --color blue
    }
    catch (const std::exception& err) {
        cerr << err.what() << std::endl;
        cerr << program;
        exit(1);
    }
    string testName = program.get<string>("testName"), taskName = program.get<string>("taskName");
    int n = program.get<int>("n");
    bool silentPass = !program.get<bool>("loudPass");

    vector<string> possibleTests {"MAX_INT", "MIN_INT", "MAX_STRING"};
    vector<string> possibleTasks {"RMQ", "Powers2", "MSB", "Queries"};
    if (find(possibleTests.begin(), possibleTests.end(), testName) == possibleTests.end())
        throw invalid_argument("Test name (" + testName +") is not supported");
    if (find(possibleTasks.begin(), possibleTasks.end(), taskName) == possibleTasks.end()) 
        throw invalid_argument("Task name (" + taskName + ") is not supported");

    if (testName == "MIN_INT") {
        auto [arr, queries] = readDataInput<int>(testName, n);

        int N=arr.size();
        if (N==0) {throw invalid_argument("arr empty!");}
        RMQ<int> rmq(arr);

        testRMQTemplate(arr, rmq, queries, testName, taskName, n, silentPass);
    }
    else if (testName == "MAX_INT") {
        auto [arr, queries] = readDataInput<int>(testName, n);

        int N=arr.size();
        if (N==0) {throw invalid_argument("arr empty!");}
        struct MyComparator {
            bool operator()(const int a, const int b) const {
                return a > b;
            }
        };
        RMQ<int, MyComparator> rmq(arr);

        testRMQTemplate(arr, rmq, queries, testName, taskName, n, silentPass);
    }
    else {
        auto [arr, queries] = readDataInput<string>(testName, n, readVectorStringGetline<1>);

        int N=arr.size();
        if (N==0) {throw invalid_argument("arr empty!");}

        struct MyComparator {
            bool operator()(const string& a, const string& b) const {
                return a > b;
            }
        };
        RMQ<string, MyComparator> rmq(arr);
        
        testRMQTemplate(arr, rmq, queries, testName, taskName, n, silentPass);
    }
    // testRMQ({1,3,-1,-3,5,3,6,7}, {{1,1}, {2,3}}, {1, 3}, {-1, 0, 1, 1, 2, 2, 2, 2, 3}, {1,2,4,8}, {
    //     {0, 1, 2, 3, 4, 5, 6, 7}, {0, 2, 3, 3, 5, 5, 6}, {3, 3, 3, 3, 5}, {3}
    //     }, "MIN_INT"
    // );
    // testRMQMax({1,3,-1,-3,5,3,6,7}, {{1,1}, {2,3}}, {1,2}, {-1,0,1,1,2,2,2,2,3}, {1,2,4,8},{
    //     {0, 1, 2, 3, 4, 5, 6, 7}, {1, 1, 2, 4, 4, 6, 7}, {1, 4, 4, 6, 7}, {7}
    //     }, "MAX_INT"
    // );
    // testRMQMaxString({"aa", "a", "b", "ba", "ac", ""}, {{1,1}, {2,3}}, {1, 3}, {-1,0,1,1,2,2,2}, {1,2,4}, {
    //     {0, 1, 2, 3, 4, 5}, {0, 2, 3, 3, 4}, {3, 3, 3}
    // },  "MAX_STRING");
    return 0;
}