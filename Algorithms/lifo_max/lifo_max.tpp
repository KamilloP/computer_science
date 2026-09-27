// LifoMax implementation

template<typename T, typename Comp = std::less<T>>
T max(const T& a, const T& b, Comp comp = Comp{}) {
    if (comp(a, b)) {return b;}
    return a;
}

template<typename T, typename Comp>
void LifoMax<T, Comp>::push(const T& e) {
    elements.push(e); // We push a copy here
    if (!maximum.empty()) {
        maximum.push(::max(maximum.top(), e, comp));
    }
    else {
        maximum.push(e);
    }
}

template<typename T, typename Comp>
void LifoMax<T, Comp>::pop() {
    if (elements.empty()) {
        throw std::out_of_range("LifoMax::pop(): empty queue");
    }
    elements.pop();
    maximum.pop();
}

template<typename T, typename Comp>
T LifoMax<T, Comp>::top() {
    if (elements.empty()) {
        throw std::out_of_range("LifoMax::top(): empty queue");
    }
    return elements.top();
}

template<typename T, typename Comp>
T LifoMax<T, Comp>::max() {
    if (elements.empty()) {
        throw std::out_of_range("LifoMax::max(): empty queue");
    }
    return maximum.top();
}

template<typename T, typename Comp>
size_t LifoMax<T, Comp>::size() {
    return elements.size();
}

template<typename T, typename Comp>
bool LifoMax<T, Comp>::empty() {
    return elements.empty();
}