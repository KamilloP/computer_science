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
void test(const std::vector<T>& result, const std::vector<T>& expected, const std::string& testName) {
    if (expected == result) {
        std::cout << "Test " << testName << " passed\n";
    }
    else {
        std::cout << "Test " << testName << " failed:\nresult=";
        printVector(result);
        std::cout << "expected=";
        printVector(expected);
        throw std::logic_error( "expected != result" );
    }
}