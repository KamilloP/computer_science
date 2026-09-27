class Solution {
private:
int _lengthOfLongestSubstring(string s) {
        if (s.length() == 0) {return 0;}
        int indices[256];
        int best = 1, curr = 1;
        fill_n(indices, 256, -1); // From algorithm library
        queue<int> Q;
        Q.push(int(s[0]));
        indices[Q.front()] = 0;
        cout << "+" << s[0];
        for (int i = 1; i < s.length(); i++) {
            int id = int(s[i]);
            if (indices[id] == -1) {
                cout << "+" << s[i];
                curr++;
                indices[id] = i;
                Q.push(id);
                best = max(best, curr);
            }
            else {
                while (Q.front() != id) {
                    cout << "-" << s[i];
                    curr--;
                    indices[Q.front()] = -1;
                    Q.pop();
                }
                cout << "=" << s[i];
                Q.pop(); // We remove current letter from the past.
                Q.push(id); // We insert current letter.
                indices[id] = i;
            }
        }
        // while (!Q.empty()) {Q.pop();}
        return best;
    }
public:
    int lengthOfLongestSubstring(string s) {
        if (s.length() == 0) {return 0;}
        int indices[256];
        int best = 1, from = 0;
        fill_n(indices, 256, -1);
        indices[int(s[0])]=0;
        for (int i = 1; i < s.length(); i++) {
            int id = int(s[i]);
            if (indices[id] < from) {
                best = max(best, i-from+1);
            }
            else {
                while (s[from] != s[i]) {from++;}
                from++;
            }
            indices[id] = i;
        }
        return best;
    }
};
