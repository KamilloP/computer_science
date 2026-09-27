// Tags: dp, FifoMax
template<typename Comp = less<int>>
class FifoMax {
private:
    deque<pair<int, int>> maximum;
    queue<int> elements;
    Comp comp;
    int pos;
public:
    FifoMax(Comp c = Comp{}): pos(0), comp(c) {}
    ~FifoMax() {}
    bool empty() {return elements.empty();}
    size_t size() {return elements.size();}
    int back() {
        if (elements.empty()) {
            throw out_of_range("FifoMax::back(): empty queue");
        }
        return elements.back();
    }
    int front() {
        if (elements.empty()) {
            throw out_of_range("FifoMax::front(): empty queue");
        }
        return elements.front();
    }
    int max() {
        if (elements.empty()) {
            throw out_of_range("FifoMax::max(): empty queue");
        }
        return maximum.front().first;
    }
    void pop();
    void push(int e);
};

template<typename Comp>
void FifoMax<Comp>::pop() {
    if (empty()) {
        throw out_of_range("FifoMax::top(): empty queue");
    }
    elements.pop();
    if (maximum.front().second <= pos-int(elements.size())) {
        maximum.pop_front();
    }
}

template<typename Comp>
void FifoMax<Comp>::push(int e) {
    pos++;
    elements.push(e);
    while (!maximum.empty() && !comp(e, maximum.back().first)) {
        maximum.pop_back();
    }
    maximum.push_back(make_pair(e, pos));
}

class Solution {
private:
    void _printVector(const vector<int>& v) {
        cout << "[";
        for (int i=0; i+1<int(v.size()); i++) {
            cout << v[i] << ", ";
        }
        if (v.size() > 0) {
            cout << v[v.size()-1];
        }
        cout << "]\n";
    }

    vector<int> _longestProperRight(const vector<int>& nums, int k) {
        const int N=nums.size();
        FifoMax<> maximum;
        FifoMax<greater<int>> minimum;
        vector<int> longest;
        int e = 0;
        
        // We add elements just to be able to remove them at the beginning,
        // invariant is that it is always possible in the loop.
        maximum.push(-1);
        minimum.push(-1);

        for (int i=0; i<N; i++) {
            minimum.pop();
            maximum.pop();
            if (e<N) {
                int minVal, maxVal;
                if (!minimum.empty()) {
                    minVal = min(minimum.max(), nums[e]);
                    maxVal = max(maximum.max(), nums[e]);
                }
                else {
                    minVal = maxVal = nums[e];
                }
                while (e<N && maxVal-minVal <= k) {
                    minimum.push(nums[e]);
                    maximum.push(nums[e]);
                    e++;
                    if (e<N) {
                        minVal = min(minimum.max(), nums[e]);
                        maxVal = max(maximum.max(), nums[e]);
                    }
                }
            }
            longest.push_back(e);
        }
        return longest;
    }
    int _subModulo(int l, int r, const int prime=1000000007) {
        return (prime+l-r) % prime;
    }
public:
    int countPartitions(vector<int>& nums, int k) {
        const int prime = 1000000007;
        int N = nums.size();
        auto longest = _longestProperRight(nums, k);
        // _printVector(longest);
        vector<int> dp (N+2, 0); /*
            Currently prefix sum of reversed dp, but later we fix it.
            dp[N+1]=0, dp[N]=1 -> easier computation of segment.
        */
        dp[N]=1;
        for (int i=N-1; i>=0; i--) {
            int e = longest[i];
            dp[i] = _subModulo(dp[i+1], dp[e+1]);
            dp[i] = (dp[i]+dp[i+1]) % prime;
        }
        // _printVector(dp);
        return _subModulo(dp[0], dp[1]);
    }
};