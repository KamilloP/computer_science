#include <bits/stdc++.h>
#include "solution/solution.h"
#include "solution/trie/trie.h"

using namespace std;

void printVector(std::vector<int> v) {
    cout << '[';
    for (int i=0; i+1 < int(v.size()); i++) {
       cout << v[i] << ", ";
    }
    if (v.size() > 0) {cout << v[v.size()-1];}
    cout << "]\n";
}

// ifstream CANNOT be copied, it needs referencing!!!
int readInt(ifstream& stream) {
    string temp;
    getline(stream, temp);
    return stoi(temp);
}

string readString(ifstream& stream) {
    string temp;
    getline(stream, temp);
    return temp;
}

void test(int nr) {
    ifstream input_file("tests/" + to_string(nr) + ".in");
    ifstream output_file("tests/" + to_string(nr) + ".out");
    if (!input_file) {
        cerr << "Cannot open 'tests/" + to_string(nr) + ".in\n";
        throw 1;
    }
    if (!output_file) {
        cerr << "Cannot open 'tests/" + to_string(nr) + ".out\n";
        throw 1;
    }
    string txt = readString(input_file);
    int W = readInt(input_file);
    vector<string> words;
    for (int i=0; i<W; i++) {
        words.push_back(readString(input_file)); 
    }
    Solution S;
    vector<int> output = S.findSubstring(txt, words);

    // Out file:
    int R = readInt(output_file);
    vector<int> expected;
    for (int i=0; i<R; i++) {
        expected.push_back(readInt(output_file));
    }
    // Comparison:
    if (expected != output) {
        cerr << "Different answers!\nExpected: ";
        printVector(expected);
        cerr << "Output: ";
        printVector(output);
        cerr << "\n";
    }
    // while (getline(input_file, line)) {
    //     cout << line << '\n';
    // }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "No test number chosen!\n";
        return 1;
    }
    for (int i=1; i<argc; i++) {
        char* arg= argv[i];
        int nr = atoi(arg);
        test(nr);
    }
    return 0;
}