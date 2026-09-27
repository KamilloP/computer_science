#include <iostream>
#include "trie.h"
/*
Basic operators:
*/

Trie::Trie() : b(0), e(0), id(-1), nr(0), src{nullptr} {} // Important for root.

Trie::Trie(int begin, int end, int idx, int number, const std::string* source) : 
    b(begin), e(end), id(idx), nr(number), src(source) {
}

Trie::Trie(const Trie& t) : b(t.b), e(t.e), id(t.id), nr(t.nr), src(t.src) {
    for (auto s: t.sons) {
        sons.push_back(new Trie(*s));
    }
}

Trie::~Trie() {for (auto s : sons) {delete s;}}
// Note: `const int e; ... Trie(const Trie& t) {e=t.e; ...}` is not proper. We need
// initializing list: `Trie(const Trie& t) : e(t.e) { ...}`

Trie& Trie::operator=(const Trie& other) {
    // Problem is `u = u.sons[0];`, deepcopy is not sufficient for this. 
    // Solution is "copy and swap idiom": 
    // 1) we make deepcopy `temp`,
    // 2) remove whole current structure `*this`,
    // 3) copy structure `temp` to our,
    // 4) before destructor of `temp` make sure we do not remove any substructure.
    if (this == &other) {return *this;}
    Trie temp = Trie(other);
    for (auto s: sons) {delete s;}
    b = temp.b;
    e = temp.e;
    id = temp.id;
    nr = temp.nr;
    src = temp.src;
    sons = temp.sons;
    temp.sons.clear(); /* 
    Without it destructor of temp will 
    remove all the nodes of temp, thus this.sons will be dangling pointers.
    We use vector destructor `temp.sons`, which runs destructor of `temp.sons[i]`,
    but `temp.sons[i]` is pointer and destructor of pointer does not remove object that
    pointer points to.
    */
    return *this;
}

/*
Proper methods
*/
void Trie::push(const std::string& word, const int pos, const int idx) {
    int i=0;
    while (pos+i < int(word.size()) && b+i < e && (*src)[b+i] == word[pos+i]) {i++;}
    if (pos+i == int(word.size())) {
        if (b+i == e) {
            if (id == -1) {id = idx;}
            nr++;
        }
        else {
            Trie* newT = new Trie(b+i, e, id, nr, src);
            for (auto s: sons) {newT->sons.push_back(s);}
            sons.clear();
            sons.push_back(newT);
            e = b+i;
            id = idx;
            nr = 1;
        }
    }
    else if (b+i == e) {
        char letter = word[pos+i];
        int j = 0;
        // `(*(sons[j]->src))` returns `const string&`, not `string`, thus
        // it is correct (cause faster). 
        while (j < int(sons.size()) && (*(sons[j]->src))[0] != letter) {j++;}
        if (j < int(sons.size())) {
            sons[j]->push(word, pos+i, idx);
        }
        else {
            Trie* newT = new Trie(pos+i, word.size(), idx, 1, &word);
            sons.push_back(newT);
        }
    }
    else {
        // src[b+i] != word[pos+i]
        Trie* newTword = new Trie(pos+i, word.size(), idx, 1, &word);
        Trie* newTcontinuation = new Trie(b+i, e, id, nr, src);
        for (auto s: sons) {
            newTcontinuation->sons.push_back(s);
        }
        sons.clear();
        sons.push_back(newTword);
        sons.push_back(newTcontinuation);
        e = b+i;
        id = -1;
        nr = 0;
    }
}

void Trie::findCounter(std::vector<int>& counter) {
    if (id > -1) {counter[id] = nr;}
    for (auto s: sons) {
        s->findCounter(counter);
    }
}

void Trie::print() {
    std::cout << "[" << b << " " << e << " " << id << " " << nr << " " << src << " ";
    for (auto s: sons) {s->print();}
    std::cout << "]";
}