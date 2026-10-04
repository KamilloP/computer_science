template<typename T>
void printVector(const std::vector<T>& v) {
    std::cout << "[";
    for (int i=0; i+1<int(v.size()); i++) {
        std::cout << v[i] << ", ";
    }
    if (v.size() > 0) {
        std::cout << v[v.size()-1]; 
    }
    std::cout << "]\n";
}

template<typename T>
void printVector2(const std::vector<std::vector<T>>& v) {
    std::cout << "[";
    for (int i=0; i+1<int(v.size()); i++) {
        printVector(v[i]);
        std::cout << ", ";
    }
    if (v.size() > 0) {
        printVector(v[v.size()-1]);
    }
    std::cout << "]\n";
}

template<typename T>
void test(
    const std::vector<T>& result, 
    const std::vector<T>& expected, 
    const std::string& testName, 
    bool silentPass
) {
    if (expected == result) {
        if (!silentPass) {
            std::cout << "Test " << testName << " passed\n";
        }
    }
    else {
        std::cout << "Test " << testName << " failed:\nresult=";
        printVector(result);
        std::cout << "expected=";
        printVector(expected);
        throw std::logic_error( "expected != result" );
    }
}

template<typename T>
void test2(
    const std::vector<std::vector<T>>& result, 
    const std::vector<std::vector<T>>& expected, 
    const std::string& testName, 
    bool silentPass
) {
    if (expected == result) {
        if (!silentPass) {
            std::cout << "Test " << testName << " passed\n";
        }
    }
    else {
        std::cout << "Test " << testName << " failed:\nresult=";
        printVector2(result);
        std::cout << "expected=";
        printVector2(expected);
        throw std::logic_error( "expected != result" );
    }
}

template<typename T>
std::vector<T> readVector(std::istream& input) {
    std::vector<T> result;
    int n;
    input >> n;
    if (n < 0) {
        throw std::invalid_argument(
            "Number of elements should be non-negative (n = " + std::to_string(n) + ")"
        );
    }
    for (int i=0; i<n; i++) {
        T temp;
        input >> temp;
        result.push_back(temp);
    }
    return result;
}

std::vector<std::string>  readVectorStringGetline(std::istream& input) {
    std::vector<std::string> result;
    int n;
    std::string nStr;
    std::getline(input, nStr);
    n = std::stoi(nStr);

    if (n < 0) {
        throw std::invalid_argument(
            "Number of elements should be non-negative (n = " + std::to_string(n) + ")"
        );
    }
    for (int i=0; i<n; i++) {
        std::string temp;
        std::getline(input, temp);
        result.push_back(temp);
    }
    return result;
}

template<typename T>
std::vector<std::vector<T>> readVector2(std::istream& input) {
    std::vector<std::vector<T>> result;
    int n;
    input >> n;
    if (n < 0) {
        throw std::invalid_argument(
            "Number of elements should be non-negative (n = " + std::to_string(n) + ")"
        );
    }
    for (int i=0; i<n; i++) {
        std::vector<T> temp = readVector<T>(input);
        result.push_back(temp);
    }
    return result;
}

std::vector<std::vector<std::string>> readVector2StringGetline(std::istream& input) {
    std::vector<std::vector<std::string>> result;
    int n;
    input >> n;
    if (n < 0) {
        throw std::invalid_argument(
            "Number of elements should be non-negative (n = " + std::to_string(n) + ")"
        );
    }
    for (int i=0; i<n; i++) {
        auto temp = readVectorStringGetline(input);
        result.push_back(temp);
    }
    return result;
}

template<typename F>
Graph readGraph(F funcAddEdge, bool tree=false, std::istream& input = std::cin) {
    int V, E;
    input >> V >> E;
    if (V < 0) {
        throw std::invalid_argument(
            "Number of vertices should be non-negative (V = " + std::to_string(V) + ")"
        );
    }
    if (E < 0) {
        throw std::invalid_argument(
            "Number of edges should be non-negative (E = " + std::to_string(E) + ")"
        );
    }
    if (tree && E != V-1) {
        throw std::invalid_argument(
            "Number of edges in tree should be equal to V-1 (E = " + std::to_string(E) + 
            ", V = " + std::to_string(V) + ")"
        );
    }
    std::vector<int> neighbours;
    std::vector<std::vector<int>> edges(V , neighbours);
    for (int i=0; i<E; i++) {
        int a, b;
        input >> a >> b;
        if (a < 0 || a >= V) {
            throw std::invalid_argument(
                "Vertex does not exist (a = " + std::to_string(a) + ", V = " + std::to_string(V) + ")"
            );
        }
        if (b < 0 || b >= V) {
            throw std::invalid_argument(
                "Vertex does not exist (b = " + std::to_string(b) + ", V = " + std::to_string(V) + ")"
            );
        }
        funcAddEdge(a, b, edges);
    }
    return std::tuple(V, E, edges);
}

Graph readUndirectedGraph(bool tree, std::istream& input) {
    auto func = [](int a, int b, std::vector<std::vector<int>>& edges) {
        edges[a].push_back(b);
        edges[b].push_back(a);
    };
    return readGraph(func, tree, input);
}

Graph readDirectedGraph(std::istream& input) {
    auto func = [](int a, int b, std::vector<std::vector<int>>& edges) {
        edges[a].push_back(b);
    };
    return readGraph(func, false, input);
}

Graph readTree(std::istream& input) {
    Graph graph = readUndirectedGraph(true, input);
    if (!isProperTree(graph))
        throw std::logic_error("Graph is not a proper tree!");
    return graph;
}

std::tuple<std::string, int, bool> analyzeMainArguments(int argc, char* argv[]) {
    std::string testName;
    int n;
    bool silentPass=true;
    if (argc < 2) {
        throw std::invalid_argument("Test type has not been defined!\n");
    }
    else if (argc < 3) {
        throw std::invalid_argument("Test number has not been defined!\n");
    }
    else if (argc == 4) {
        if (std::string(argv[3]) == "--loudPass") 
            silentPass = false;
        else
            throw std::invalid_argument("Optional argument is not `--loudPass`");
    }
    else if (argc > 4){
        throw std::invalid_argument("Too many arguments!\n");
    }
    testName = argv[1];
    try {
        n = std::stoi(std::string(argv[2]));
        // atoi has undefined behaviour and does not throw, but stoi throws exceptions
        // (invalid_argument is sth goes wrong).   
    }
    catch (std::invalid_argument const& e) {
        std::cerr << "Could not cast test number string to integer: " << e.what();
        throw e;
    }
    return std::tuple(testName, n, silentPass);
}