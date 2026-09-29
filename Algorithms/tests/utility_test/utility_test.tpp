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