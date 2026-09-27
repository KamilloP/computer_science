class MinStack {
// Begin add
private:
    stack<int> elements;
    stack<int> minimum;
// End add
public:
    MinStack() {
        // Nothing
    }
    
    void push(int value) {
        elements.push(value);
        if (minimum.empty()) {
            minimum.push(value);
        }
        else {
            int current_min = minimum.top();
            minimum.push(min(current_min, value));
        }
    }
    
    void pop() {
        if (!elements.empty()) {
            elements.pop();
            minimum.pop();
        }
    }
    
    int top() {
        return elements.top();
    }
    
    int getMin() {
        return minimum.top();
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */