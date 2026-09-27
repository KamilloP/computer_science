// Tags: kmp, lcp, trie, hash
class Solution {
private:
  class Trie {
    // The safest: unique_ptr.
    // Assumes that only root have src = nullptr, all others have proper substrings 
    // (positive length).
  public:
    /*
     Attributes:
     */
    int b, e, id, nr;
    const string* src; /* 
     We can change where `src` points to, but we cannot modify `*src`.
     `const string const * src;` -> Both: we cannot modify `src` and `*src`.
     */
    vector<Trie*> sons;
    
    /*
     Basic operators:
     */
    Trie() : b(0), e(0), id(-1), nr(0), src{nullptr} {} // Important for root.
    Trie(int begin, int end, int idx, int number, const string* source) : 
      b(begin), e(end), id(idx), nr(number), src(source) {}
    Trie(const Trie& t) : b(t.b), e(t.e), id(t.id), nr(t.nr), src(t.src) {
      for (auto s: t.sons) {
        sons.push_back(new Trie(*s));
      }
    }
    ~Trie() {for (auto s : sons) {delete s;}}
    // Note: `const int e; ... Trie(const Trie& t) {e=t.e; ...}` is not proper. We need
    // initializing list: `Trie(const Trie& t) : e(t.e) { ...}`
    
    // We will not use operator=, but as an exercise we define it.
    Trie& operator=(const Trie& other) {
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
    
    void push(const string& word, const int pos, const int idx) {
      int i=0;
      while (pos+i < word.size() && b+i < e && (*src)[b+i] == word[pos+i]) {i++;}
      if (pos+i == word.size()) {
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
        while (j < sons.size() && (*(sons[j]->src))[0] != letter) {j++;}
        if (j < sons.size()) {
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
    void findCounter(vector<int>& counter) {
      if (id > -1) {counter[id] = nr;}
      for (auto s: sons) {
        s->findCounter(counter);
      }
    }
    void print() {
      cout << "[" << b << " " << e << " " << id << " " << nr << " " << src << " ";
      for (auto s: sons) {s->print();}
      cout << "]";
    }
  };
  
  /*
   Auxilliary functions:
   */
  void _printVector(vector<int> v) {
    cout << '[';
    for (int i=0; i+1 < v.size(); i++) {
      cout << v[i] << ", ";
    }
    if (v.size() > 0) {cout << v[v.size()-1];}
    cout << "]\n";
  }
  vector<int> _lsp(const string& txt) {
    if (txt.length() == 0) {return {-1};} 
    vector<int> lsp = {-1,0};
    for (int i=1; i < txt.length(); i++) {
      int j=i;
      while (j>0 && txt[i] != txt[lsp[j]]) {j = lsp[j];}
      lsp.push_back(lsp[j]+1);
    }
    return lsp;
  }
  vector<int> _kmpAllOccurences(const string& txt, const string& pat) {
    // Let n=txt.length(), m=pat.length().
    // Time complexity: O(n+m). 
    // Memory complexity: O(m).
    if (pat.length() > txt.length()) {return {};}
    if (pat.length() == 0) {throw -1;}
    auto lsp = _lsp(pat);
    // cout << "lsp: ";
    // _printVector(lsp);
    vector<int> occurences;
    int common=0;
    for (int i=0; i<txt.length(); i++) {
      while (common >= 0 && txt[i] != pat[common]) {common = lsp[common];}
      common++;
      // cout << common << ", ";
      if (common == pat.length()) {
        occurences.push_back(i+1-common);
        common = lsp[common];
      }
    }
    // cout << "\n";
    return occurences;
  }
  vector<int> _findCounterTrie(vector<string>& words) {
    // Time complexity: W N logN
    Trie root {};
    for (int i=0; i < words.size(); i++) {
      root.push(words[i], 0, i);
    }
    vector<int> counter (words.size(), 0);
    root.findCounter(counter);
    return counter;
  }
  
  vector<int> _findCounter(vector<string>& words) {
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
    auto comp = [](const pair<string*, int>& a, const pair<string*, int>& b) {
      return *(a.first) < *(b.first) || *(a.first) == *(b.first) && a.second < b.second;
    };
    vector<pair<string*, int>> pairs;
    for (int i=0; i < words.size(); i++) {
      pairs.push_back(make_pair(&words[i], i));
    }
    sort(pairs.begin(), pairs.end(), comp);
    vector<int> counter (words.size(), 0);
    counter[pairs[0].second]++;
    int last = 0;
    for (int i=1; i < pairs.size(); i++) {
      if (*(pairs[i].first) != *(pairs[last].first)) {last = i;}
      counter[pairs[last].second]++;
    }
    return counter;
  }
  pair<vector<int>, vector<int>> _preprocessing(const string& s, vector<string>& words) {
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
    vector<int> begins (s.length(), -1);
    // vector<int> counter = _findCounter(words);
    vector<int> counter = _findCounterTrie(words);
    for (int i=0; i < words.size(); i++) {
      if (counter[i] > 0) {
        vector<int> occ = _kmpAllOccurences(s, words[i]);
        // cout << "occ: ";
        // _printVector(occ);
        for (int j : occ) {begins[j] = i;}
      }
    }
    return make_pair(begins, counter);
  }
  
public:
  vector<int> findSubstring(string s, vector<string>& words) {
    const int N = words.size(), M = s.length(), W = words[0].length();
    if (N*W > M) {return {};}
    vector<int> result;
    auto [begins, counter] = _preprocessing(s, words);
    // cout << "begins: ";
    // _printVector(begins);
    // cout << "ends: ";
    // _printVector(counter);
    for(int i=0; i < W; i++) {
      vector<int> multiset = counter; // copy
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
};

// class Solution {
// private:
//     void _printVector(vector<int> v) {
//         cout << '[';
//         for (int i=0; i+1 < v.size(); i++) {
//             cout << v[i] << ", ";
//         }
//         if (v.size() > 0) {cout << v[v.size()-1];}
//         cout << "]\n";
//     }
//     vector<int> _lsp(const string& txt) {
//         if (txt.length() == 0) {return {-1};} 
//         vector<int> lsp = {-1,0};
//         for (int i=1; i < txt.length(); i++) {
//             int j=i;
//             while (j>0 && txt[i] != txt[lsp[j]]) {j = lsp[j];}
//             lsp.push_back(lsp[j]+1);
//         }
//         return lsp;
//     }
//     vector<int> _kmpAllOccurences(const string& txt, const string& pat) {
//         // Let n=txt.length(), m=pat.length().
//         // Time complexity: O(n+m). 
//         // Memory complexity: O(m).
//         if (pat.length() > txt.length()) {return {};}
//         if (pat.length() == 0) {throw -1;}
//         auto lsp = _lsp(pat);
//         // cout << "lsp: ";
//         // _printVector(lsp);
//         vector<int> occurences;
//         int common=0;
//         for (int i=0; i<txt.length(); i++) {
//             while (common >= 0 && txt[i] != pat[common]) {common = lsp[common];}
//             common++;
//             // cout << common << ", ";
//             if (common == pat.length()) {
//                 occurences.push_back(i+1-common);
//                 common = lsp[common];
//             }
//         }
//         // cout << "\n";
//         return occurences;
//     }
//     vector<int> _findCounter(vector<string>& words) {
//         // Time complexity: O(W N logN). Memory complexity: O(N).
//         // Important: THERE ARE WAYS TO IMPROVE THIS SOLUTION.
//         // 1) We can obtain faster sorting by using trie. We keep vector of existing sons in a node instead of size of alphabet sons.
//         //  1.1) Simple trie - each node one letter. Memory: O(N*W). Time: O(N*W+N^2) = O(N*W) if N<W, which is usually the case.
//         //  1.2) Trie harder: each node substring. Same time as simple trie, but worse constant. Memory better - O(N^2).
//         // 2) Another approach is using hashes to compare strings. This way:
//         //  2.1) just hashes without checking: T = O(N*W), M = O(1). Low positive chance of error.
//         //  2.2) hashes with hashtable (we add hash function). Risky cause comparing elements takes O(W), which is very possible if two elements in the same place in hash table. 
//         //       We would need big starting hashtable to decrease this chance. No risk of error. Expected memory and time complexity same as before.
//         // Trie 1.2 seems the best - computing hashes is slow, a little bit risky, O(N^2) is very small in our case.
//         auto comp = [](const pair<string*, int>& a, const pair<string*, int>& b) {
//             return *(a.first) < *(b.first) || *(a.first) == *(b.first) && a.second < b.second;
//         };
//         vector<pair<string*, int>> pairs;
//         for (int i=0; i < words.size(); i++) {
//             pairs.push_back(make_pair(&words[i], i));
//         }
//         sort(pairs.begin(), pairs.end(), comp);
//         vector<int> counter (words.size(), 0);
//         counter[pairs[0].second]++;
//         int last = 0;
//         for (int i=1; i < pairs.size(); i++) {
//             if (*(pairs[i].first) != *(pairs[last].first)) {last = i;}
//             counter[pairs[last].second]++;
//         }
//         return counter;
//     }
//     pair<vector<int>, vector<int>> _preprocessing(const string& s, vector<string>& words) {
//         /* 
//         Return 2 vectors: `begins` and `counter`.
//         We might have the same words. Thus:
//         1) counter:
//             If counter[i] > 0, \forall_{j<i} words[i]!=words[j] && 
//                 number of words same as words[i] is counter[i].
//             Otherwise \exists_{j<i} words[i] = words[j].
//         2) begins:
//             if begins[i] = -1 then none of words start at position `i`,
//             otherwise words[begins[i]] starts at position `i`, moreover counter[begins[i]] > 0.
//         */
//         vector<int> begins (s.length(), -1);
//         vector<int> counter = _findCounter(words);
//         for (int i=0; i < words.size(); i++) {
//             if (counter[i] > 0) {
//                 vector<int> occ = _kmpAllOccurences(s, words[i]);
//                 // cout << "occ: ";
//                 // _printVector(occ);
//                 for (int j : occ) {begins[j] = i;}
//             }
//         }
//         return make_pair(begins, counter);
//     }

// public:
//     vector<int> findSubstring(string s, vector<string>& words) {
//         const int N = words.size(), M = s.length(), W = words[0].length();
//         if (N*W > M) {return {};}
//         vector<int> result;
//         auto [begins, counter] = _preprocessing(s, words);
//         // cout << "begins: ";
//         // _printVector(begins);
//         // cout << "ends: ";
//         // _printVector(counter);
//         for(int i=0; i < W; i++) {
//             vector<int> multiset = counter; // copy
//             int p1=i, p2=i;
//             while (p1 + N*W <= M) {
//                 while (p2 < p1 + N*W && begins[p2] > -1 && multiset[begins[p2]] > 0) {
//                     multiset[begins[p2]]--;
//                     p2 += W;
//                 }
//                 if (p2 == p1 + N*W) {
//                     result.push_back(p1);
//                     multiset[begins[p1]]++;
//                 }
//                 else if (p2 == p1) {
//                     p2 = p1+W;
//                 }
//                 else {
//                     // begins[p2] == -1 || multiset[begins[p2]] == 0
//                     multiset[begins[p1]]++;
//                 }
//                 p1 += W;
//             }
//         }
//         return result;
//     }
// };
