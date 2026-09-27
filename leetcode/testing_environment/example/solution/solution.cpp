#include "solution.h"
#include "trie/trie.h"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

void Solution::_printVector(std::vector<int> v) {
    std::cout << '[';
    for (int i=0; i+1 < int(v.size()); i++) {
      std::cout << v[i] << ", ";
    }
    if (v.size() > 0) {std::cout << v[v.size()-1];}
    std::cout << "]\n";
}

std::vector<int> Solution::_lsp(const std::string& txt) {
    if (txt.length() == 0) {return {-1};} 
    std::vector<int> lsp = {-1,0};
    for (int i=1; i < int(txt.length()); i++) {
      int j=i;
      while (j>0 && txt[i] != txt[lsp[j]]) {j = lsp[j];}
      lsp.push_back(lsp[j]+1);
    }
    return lsp;
}

std::vector<int> Solution::_kmpAllOccurences(const std::string& txt, const std::string& pat) {
    // Let n=txt.length(), m=pat.length().
    // Time complexity: O(n+m). 
    // Memory complexity: O(m).
    if (pat.length() > txt.length()) {return {};}
    if (pat.length() == 0) {throw -1;}
    auto lsp = _lsp(pat);
    // cout << "lsp: ";
    // _printVector(lsp);
    std::vector<int> occurences;
    int common=0;
    for (int i=0; i < int(txt.length()); i++) {
        while (common >= 0 && txt[i] != pat[common]) {common = lsp[common];}
        common++;
        // cout << common << ", ";
        if (common == int(pat.length())) {
            occurences.push_back(i+1-common);
            common = lsp[common];
        }
    }
    // cout << "\n";
    return occurences;
}

std::vector<int> Solution::_findCounterTrie(std::vector<std::string>& words) {
    // Time complexity: W N logN
    Trie root {};
    for (int i=0; i < int(words.size()); i++) {
      root.push(words[i], 0, i);
    }
    std::vector<int> counter (words.size(), 0);
    root.findCounter(counter);
    return counter;
}

std::vector<int> Solution::_findCounter(std::vector<std::string>& words) {
    // Time complexity: O(W N logN). Memory complexity: O(N).
    // Important: THERE ARE WAYS TO IMPROVE THIS SOLUTION.
    // 1) We can obtain faster sorting by using trie. We keep vector of existing sons in a node instead of size of alphabet sons.
    //  1.1) Simple trie - each node one letter. Memory: O(N*W). Time: O(N*W+N^2) = O(N*W) if N<W, which is usually the case.
    //  1.2) Trie harder: each node substring. Same time as simple trie, but worse constant. Memory better - O(N^2).
    // 2) Another approach is using hashes to compare strings. This way:
    //  2.1) just hashes without checking: T = O(N*W), M = O(1). Low positive chance of error.
    //  2.2) hashes with hashtable (we add hash function). Risky cause comparing elements takes O(W), which is very possible if two elements in the same place in hash table. 
    //       We would need big starting hashtable to decrease this chance. No risk of error. Expected memory and time complexity same as before.
    // Trie 1.2 seems the best - computing hashes is slow, a little bit risky, O(N^2) is very small in our case.
    auto comp = [](const std::pair<std::string*, int>& a, const std::pair<std::string*, int>& b) {
        return *(a.first) < *(b.first) || (*(a.first) == *(b.first) && a.second < b.second);
    };
    std::vector<std::pair<std::string*, int>> pairs;
    for (int i=0; i < int(words.size()); i++) {
        pairs.push_back(make_pair(&words[i], i));
    }
    std::sort(pairs.begin(), pairs.end(), comp);
    std::vector<int> counter (words.size(), 0);
    counter[pairs[0].second]++;
    int last = 0;
    for (int i=1; i < int(pairs.size()); i++) {
        if (*(pairs[i].first) != *(pairs[last].first)) {last = i;}
        counter[pairs[last].second]++;
    }
    return counter;
}

std::pair<std::vector<int>, std::vector<int>> Solution::_preprocessing(const std::string& s, std::vector<std::string>& words) {
    /* 
    Return 2 vectors: `begins` and `counter`.
    We might have the same words. Thus:
    1) counter:
    If counter[i] > 0, \forall_{j<i} words[i]!=words[j] && 
    number of words same as words[i] is counter[i].
    Otherwise \exists_{j<i} words[i] = words[j].
    2) begins:
    if begins[i] = -1 then none of words start at position `i`,
    otherwise words[begins[i]] starts at position `i`, moreover counter[begins[i]] > 0.
    */
    std::vector<int> begins (s.length(), -1);
    // vector<int> counter = _findCounter(words);
    std::vector<int> counter = Solution::_findCounterTrie(words);
    for (int i=0; i < int(words.size()); i++) {
        if (counter[i] > 0) {
            std::vector<int> occ = Solution::_kmpAllOccurences(s, words[i]);
            // cout << "occ: ";
            // _printVector(occ);
            for (int j : occ) {begins[j] = i;}
        }
    }
    return make_pair(begins, counter);
}

/*
Solution:
*/

std::vector<int> Solution::findSubstring(std::string s, std::vector<std::string>& words) {
    const int N = words.size(), M = s.length(), W = words[0].length();
    if (N*W > M) {return {};}
    std::vector<int> result;
    auto [begins, counter] = _preprocessing(s, words);
    // cout << "begins: ";
    // _printVector(begins);
    // cout << "ends: ";
    // _printVector(counter);
    for(int i=0; i < W; i++) {
      std::vector<int> multiset = counter; // copy
      int p1=i, p2=i;
      while (p1 + N*W <= M) {
        while (p2 < p1 + N*W && begins[p2] > -1 && multiset[begins[p2]] > 0) {
          multiset[begins[p2]]--;
          p2 += W;
        }
        if (p2 == p1 + N*W) {
          result.push_back(p1);
          multiset[begins[p1]]++;
        }
        else if (p2 == p1) {
          p2 = p1+W;
        }
        else {
          // begins[p2] == -1 || multiset[begins[p2]] == 0
          multiset[begins[p1]]++;
        }
        p1 += W;
      }
    }
    return result;
}