class Solution {
private:
    array<int, 26> findSignature(const string& s) {
        array<int, 26> sig{}; // filled with zeros (https://en.cppreference.com/cpp/container/array)
        for (int j=0; j < s.length(); j++) {
            sig[int(s[j]-'a')]++;
        }
        return sig;
    }
    void printSignature(const array<int, 26>& sig) {
        cout << "{";
        for (int i=0; i<25; i++) {
            cout << sig[i] << ", ";
        }
        cout << sig[25] << "}";
    }
    void printSignatures(const map<array<int, 26>, int>& signatures) {
        cout << "[\n";
        for (const auto& [key, value] : signatures) {
            cout << "(key: ";
            printSignature(key);
            cout << ";\nvalue: " << value << "),\n";   
        }
        cout << "]\n";
    }
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<array<int, 26>, int> signatures;
        for (int i=0; i < strs.size(); i++) {
            // printSignature(findSignature(strs[i]));
            signatures[findSignature(strs[i])]=1;
        }
        // printSignatures(signatures);
        int val=1;
        for (auto itr = signatures.begin(); itr != signatures.end(); itr++) {
            itr->second = val;
            val++;
        }
        // printSignatures(signatures);
        int S = signatures.size();
        vector<string> current;
        vector<vector<string>> result(S, current);
        for (string& s : strs) {
            int id = signatures[findSignature(s)]-1;
            result[id].push_back(s);
        }
        return result;
    }
};