#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>
#include <string>
#include <utility>

class Solution {
private:
    /*
    Auxilliary functions:
    */
    void _printVector(std::vector<int> v);
    std::vector<int> _lsp(const std::string& txt);
    std::vector<int> _kmpAllOccurences(const std::string& txt, const std::string& pat);
    std::vector<int> _findCounterTrie(std::vector<std::string>& words);
    std::vector<int> _findCounter(std::vector<std::string>& words);
    std::pair<std::vector<int>, std::vector<int>> _preprocessing(
        const std::string& s,
        std::vector<std::string>& words
    );
public:
    std::vector<int> findSubstring(std::string s, std::vector<std::string>& words);
};

#endif