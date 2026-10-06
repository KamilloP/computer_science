#include <bits/stdc++.h>
// #include <stdexcept> // Not included because in bits/stdc++.h
#include "utility_test/utility_test.h"
#include "../graph/graph.h"
#include <argparse/argparse.hpp>

// g++ -std=c++17 -Wall -Wextra -pedantic test_rmq.cpp -o bin/test_rmq

using namespace std;

tuple<int, Graph, vector<pair<int,int>>> readDataInput(int n) {
    ifstream input_file("dataset/lca/" + to_string(n) + ".in");
    if (!input_file) {
        throw invalid_argument("No such file as `dataset/lca/" + to_string(n) + ".in`");
    }
    int root;
    input_file >> root;
    auto tree = readTree(input_file);
    if (root < 0 || root >= get<0>(tree))
        throw out_of_range("Root of tree out of range (root=" + to_string(root)  + ", V=" + to_string(get<0>(tree)) + ")!");
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
    return tuple(root, tree, queries);
}

template<int N>
VectorT<int, N> readDataExpected(const string& taskName, int n) {
    ifstream expected_file("dataset/lca/" + taskName + "/" + to_string(n) + ".out");
    if (!expected_file)
        throw invalid_argument("No such file as `dataset/lca/" + taskName + "/" + to_string(n) + ".out`");
    return readVector<int,N>(expected_file);
}

// vector<vector<int>> readDataExpected2(const string& testName, const string& taskName, int n) {
//     ifstream expected_file("dataset/rmq/" + testName + "/" + taskName + "/" + to_string(n) + ".out");
//     if (!expected_file)
//         throw invalid_argument("No such file as `dataset/rmq/" + testName + "/" + taskName + "/" + to_string(n) + ".out`");
//     return readVector2<int>(expected_file);
// }

vector<int> findLCA(const LCA& lca, const vector<pair<int, int>>& queries) {
    vector<int> result;
    for (auto [u,v] : queries) {
        result.push_back(lca.lca(u, v));
    }
    return result;
}

vector<int> computeOutput(
    const LCA& lca, 
    const vector<pair<int,int>>& queries, 
    const string& taskName
) {
    if (taskName == "Inorder")
        return lca.getInorder();
    if (taskName == "Height")
        return lca.getHeight();
    // Queries
    return findLCA(lca, queries);
}

void testLCATemplate(
    const LCA& lca, 
    const vector<pair<int, int>>& queries,
    const string& taskName,
    int n,
    bool silentPass
) {
    auto expected = readDataExpected<1>(taskName, n);
    auto output = computeOutput(lca, queries, taskName);
    test<int,1>(output, expected, taskName, silentPass);
    // or test3...
}

int main (int argc, char* argv[]) {
    argparse::ArgumentParser program("algorithms_tests");
    program.add_argument("taskName")
        .help("Name of the task (Inorder, Height or Queries");
    program.add_argument("n")
        .help("Test identifier (number)")
        .scan<'i', int>();
    program.add_argument("--loudPass")
        .help("Whether passed test should be logged or not")
        .default_value(false)
        .implicit_value(true);
    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        cerr << err.what() << std::endl;
        cerr << program;
        exit(1);
    }
    string taskName = program.get<string>("taskName");
    int n = program.get<int>("n");
    bool silentPass = !program.get<bool>("loudPass");

    vector<string> possibleTasks {"Inorder", "Height", "Queries"};
    if (find(possibleTasks.begin(), possibleTasks.end(), taskName) == possibleTasks.end()) 
        throw invalid_argument("Task name (" + taskName + ") is not supported");
    
    auto [root, tree, queries] = readDataInput(n);
    const auto& [V, E, edges] = tree;
    // Begin debug
    // cout << "(" << V << ", " << E << " ";
    // printVector2(edges);
    // cout << ")\n"; 
    // End debug
    if (V < 2) {throw invalid_argument("Number of vertices less than 2!");}
    // cout << "Read tree done!\n";
    LCA lca(root, tree);
    // cout << "lca constructed!\n";
    testLCATemplate(lca, queries, taskName, n, silentPass);
    // cout << "tests passed!\n";
    return 0;
}