// Used in problem 155

#ifndef LIFO_MAX
#define LIFO_MAX

#include<stack>
#include<functional>
#include<stdexcept>

template<typename T, typename Comp = std::less<T>>
class LifoMax {
private:
    std::stack<T> elements;
    std::stack<T> maximum;
    Comp comp;
public:
    LifoMax(Comp c = Comp{}): comp(c) {}
    ~LifoMax() {}
    void push(const T& e);
    void pop();
    T top();
    T max();
    size_t size();
    bool empty();
};

#include "lifo_max.tpp"

#endif