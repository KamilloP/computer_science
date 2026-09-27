#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

class Trie {
// The safest: unique_ptr.
// Assumes that only root have src = nullptr, all others have proper substrings 
// (positive length).
public:
    Trie();
    Trie(const Trie& t);
    ~Trie();
    Trie& operator=(const Trie& other);
    void push(const std::string& word, const int pos, const int idx);
    void findCounter(std::vector<int>& counter);
    void print();
private:
    int b, e, id, nr;
    const std::string* src;
    std::vector<Trie*> sons;
    Trie(int begin, int end, int idx, int number, const std::string* source);
};

#endif