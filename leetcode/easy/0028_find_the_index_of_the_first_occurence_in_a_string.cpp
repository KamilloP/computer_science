class Solution {
    vector<int> _lps(const string& txt) {
        if (txt.length()==0) {return {-1};}
        vector<int> lps = {-1,0};
        for (int i=1; i<txt.size(); i++) {
            int j = i;
            while (j > 0 && txt[i] != txt[lps[j]]) {j = lps[j];}
            lps.push_back(lps[j]+1);
        }
        return lps;
    }
    void printVector(vector<int> v) {
        cout << "[";
        for (int i = 0; i+1 < v.size(); i++) {
            cout << v[i] << ", ";
        }
        if (v.size() > 0) {
            cout << v[v.size()-1];
        }
        cout << "]\n";
    }
    int _kmp(const string& txt, const string& pat, char specialChar) {
        vector<int> lps = _lps(pat + specialChar + txt);
        // printVector(lps);
        for (int i = 2*pat.length() + 1; i < lps.size(); i++) {
            if (lps[i] == pat.length()) {
                return i-2*pat.length()-1;
            }
        }
        return -1;
    }
    int _kmp(const string& txt, const string& pat) {
        if (pat.length() > txt.length()) {return -1;}
        if (pat.length() == 0) {return 0;}
        vector<int> lpsPat = _lps(pat);
        // printVector(lpsPat);
        int common = 0;
        for (int i=0; i < txt.length(); i++) {
            while (common >= 0 && txt[i] != pat[common]) {common = lpsPat[common];}
            common = common+1;
            if (common == pat.length()) {return i+1-pat.length();}
        }
        return -1;
    }
    int _hash(const string& txt, const string& pat) {
        if (pat.length() > txt.length()) {return -1;}
        if (pat.length() == 0) {return 0;}
        const unsigned long long prime1 = 1000000007, prime2 = 1000000009;
        unsigned long long prime1Power = 1, patHash=0, current=0, prefix=0;
        for (int i=0; i < pat.length(); i++) {
            prime1Power = (prime1Power * prime1) % prime2;
        }
        for (char letter : pat) {
            patHash = (patHash*prime1 + int(letter)+1) % prime2;
        }
        for (int i=0; i < pat.length()-1; i++) {
            current = (current*prime1 + int(txt[i])+1) % prime2;
        }
        for (int i=pat.length()-1; i<txt.length(); i++) {
            current = (current*prime1 + int(txt[i])+1) % prime2;
            unsigned long long hash = (prime2 + current - ((prefix*prime1Power) % prime2)) % prime2;
            if (patHash == hash) {return i+1-pat.length();}
            prefix = (prefix*prime1 + int(txt[i+1-pat.length()])+1) % prime2;
        }
        return -1;
    }

public:
    int strStr(string haystack, string needle) {
        return _hash(haystack, needle);
    }
};
