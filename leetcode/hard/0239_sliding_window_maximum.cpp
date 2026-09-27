// Tags: FifoMax
class FifoMax {
private:
    deque<pair<int, int>> maximum;
    queue<int> elements;
    int pos;
public:
    FifoMax(): pos(0) {}
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

void FifoMax::pop() {
    if (empty()) {
        throw out_of_range("FifoMax::top(): empty queue");
    }
    elements.pop();
    if (maximum.front().second <= pos-int(elements.size())) {
        maximum.pop_front();
    }
}

void FifoMax::push(int e) {
    pos++;
    elements.push(e);
    while (!maximum.empty() && maximum.back().first <= e) {
        maximum.pop_back();
    }
    maximum.push_back(make_pair(e, pos));
}

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int N = nums.size();
        FifoMax fm;
        vector<int> result;
        for (int i=0; i<k; i++) {fm.push(nums[i]);}
        result.push_back(fm.max());
        for (int j=k; j<N; j++) {
            fm.push(nums[j]);
            fm.pop();
            result.push_back(fm.max());
        }
        return result;
    }
};