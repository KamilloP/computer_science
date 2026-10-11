#include <bits/stdc++.h>
// #include <stdexcept> // Not included because in bits/stdc++.h
#include "utility_test/utility_test.h"
#include "../graph/graph_definition.h"
#include "../graph/graph.h"
#include <argparse/argparse.hpp>

using namespace std;

template<typename T>
tuple<int, WeightedGraph<T>> readDataInput(int n, const string& typeName) {
    ifstream input_file("dataset/graph/dijkstra/" + typeName + "/" + to_string(n) + ".in");
    if (!input_file) {
        throw invalid_argument("No such file as `dataset/graph/dijkstra/" + typeName + "/" + to_string(n) + ".in`");
    }
    int root;
    input_file >> root;
    auto tree = readWeightedUndirectedGraph<T>(false, input_file);
    if (root < 0 || root >= get<0>(tree))
        throw out_of_range("Root of tree out of range (root=" + to_string(root)  + ", V=" + to_string(get<0>(tree)) + ")!");
    return tuple(root, tree);
}

template<typename T>
tuple<vector<int>, vector<T>> readDataExpected(int n, const string& typeName) {
    ifstream expected_file("dataset/graph/dijkstra/" + typeName + "/" + to_string(n) + ".out");
    if (!expected_file)
        throw invalid_argument("No such file as `dataset/graph/dijkstra/" + typeName + "/" + to_string(n) + ".out`");
    vector<int> prev = readVector<int,1>(expected_file);
    vector<T> dist = readVector<T, 1>(expected_file);
    return make_tuple(prev, dist);
}

template<typename T, typename Comp = equal_to<T>>
void testDijkstraTemplate(
    const string& typeName,
    const string& complexity,
    int n,
    bool silentPass,
    const Comp equal = Comp{}
) {
    auto [root, graph] = readDataInput<T>(n, typeName);
    auto [previousE, distancesE] = readDataExpected<T>(n, typeName);
    try {
        assertProperPathFromSource(root, graph, previousE, distancesE, equal);
    }
    catch (exception& e) {
        cerr << "Dijkstra:" << typeName << ":" << complexity <<
         ": Solution expected has error (bad test):\n" << e.what();
        throw e;
    }
    vector<int> previousO;
    vector<T> distancesO;
    if (complexity == "ElogV") {
        tie(previousO, distancesO) = dijkstraElogV<T>(root, graph);
    }
    else if (complexity == "ElogE") {
        tie(previousO, distancesO) = dijkstraElogE<T>(root, graph);
    }
    else {
        tie(previousO, distancesO) = dijkstra<T>(root, graph);
    }
    try {
        assertProperPathFromSource(root, graph, previousO, distancesO, equal);
    }
    catch (exception& e) {
        cerr << "Dijkstra:" << typeName << ":" << complexity << ": Output has error:\n";
        throw e;
    }
    test<T,1>(distancesO, distancesE, "Dijkstra:" + typeName + ":"  + 
        complexity + ":" + to_string(n) + string(":distances"), silentPass);
}

int main (int argc, char* argv[]) {
    argparse::ArgumentParser program("algorithms_tests");
    program.add_argument("typeName")
        .help("Type of the graph weight ('double' or 'int')");
    program.add_argument("complexity")
        .help("Complexity of the algorithm ('E+VlogV' (but has high constant), 'ElogV', 'ElogE')");
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
    string typeName = program.get<string>("typeName"), complexity = program.get<string>("complexity");
    int n = program.get<int>("n");
    bool silentPass = !program.get<bool>("loudPass");

    vector<string> possibleTypes {"double", "int"};
    vector<string> possibleComplexities {"E+VlogV", "ElogV", "ElogE"};
    if (find(possibleTypes.begin(), possibleTypes.end(), typeName) == possibleTypes.end()) 
        throw invalid_argument("Type (" + typeName + ") is not supported");
    if (find(possibleComplexities.begin(), possibleComplexities.end(), complexity) == possibleComplexities.end()) 
        throw invalid_argument("Complexity (" + complexity + ") is not supported");
    
    if (typeName == "double") {
        struct EqualWithPrecision6 {
            bool operator()(double a, double b) const {
                return std::abs(a-b) < 1e-6;
            }
        };
        testDijkstraTemplate<double, EqualWithPrecision6>(typeName, complexity, n, silentPass);
    }
    else {
        testDijkstraTemplate<int>(typeName, complexity, n, silentPass);
    }
    return 0;
}