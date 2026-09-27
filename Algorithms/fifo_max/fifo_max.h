// Useful for sliding window max (e.g. problems 239, 3578)

#ifndef FIFO_MAX
#define FIFO_MAX

#include<deque>
#include<queue>
#include<utility>
#include <functional>
#include <stdexcept>

template<typename T, typename Comp = std::less<T>>
class FifoMax {
    Comp comp;
    std::deque<std::pair<T,int>> maximum;
    std::queue<T> elements;
    int pos;
public:
    FifoMax(Comp c = Comp{}) : comp(c), pos(0) {}
    ~FifoMax() {}
    void push(const T& e); // amortized O(1)
    void pop();
    T max();
    T front();
    T back();
    size_t size();
    bool empty();
};

#include "fifo_max.tpp" 
/*
https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
*/

#endif