// FifoMax implementation

template<typename T, typename Comp>
void FifoMax<T, Comp>::push(const T& e) {
    pos++;
    elements.push(e); // e is copied here, not a reference. 
    while (!maximum.empty() && !comp(e, maximum.back().first)) {
        // maximum.back() <= e
        maximum.pop_back();
    }
    maximum.push_back(std::make_pair(e, pos));
}

template <typename T, typename Comp>
void FifoMax<T, Comp>::pop() {
    if (elements.empty()) {
        throw std::out_of_range("FifoMax::pop(): empty queue");
    }
    elements.pop();
    if (maximum.front().second <= pos-int(elements.size())) {
        maximum.pop_front();
    }
    // `maximum` was not empty if `elements` was not empty - invariant
}

template <typename T, typename Comp>
T FifoMax<T, Comp>::max() {
    if (elements.empty()) {
        throw std::out_of_range("FifoMax::max(): empty queue");
    }
    return maximum.front().first;
}

template <typename T, typename Comp>
T FifoMax<T, Comp>::front() {
    if (elements.empty()) {
        throw std::out_of_range("FifoMax::front(): empty queue");
    }
    return elements.front();
}

template <typename T, typename Comp>
T FifoMax<T, Comp>::back() {
    if (elements.empty()) {
        throw std::out_of_range("FifoMax::max(): empty queue");
    }
    return elements.back();
}

template <typename T, typename Comp>
size_t FifoMax<T, Comp>::size() {
    return elements.size();
}

template <typename T, typename Comp>
bool FifoMax<T, Comp>::empty() {
    return elements.empty();
}
