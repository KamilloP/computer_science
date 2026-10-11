// #include "fibonacci_heap.h" 
// VSC generates error

template<typename T, typename Comp>
T FibonacciHeap<T, Comp>::minVal() const {
    if (minNode == nullptr) {
        throw std::logic_error("FibonacciHeap is empty");
    }
    return minNode->val;
}

template<typename T, typename Comp>
DoublyLinkedNode<T>* FibonacciHeap<T, Comp>::insert(T val) {
    DoublyLinkedNode<T>* newNode = new DoublyLinkedNode(val);
    nrOfTrees++;
    heapSize++;
    if (!last) {
        // heap is empty
        first = minNode = last = newNode;
    }
    else {
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
        if (comp(val, minNode->val))
            minNode = newNode;
    }
    return newNode;
}

template<typename T, typename Comp>
void FibonacciHeap<T, Comp>::merge(FibonacciHeap<T, Comp>& other) {
    if (other.empty()) {return;}
    if (empty()) {
        first = other.first;
        last = other.last;
        minNode = other.minNode;
        heapSize = other.heapSize;
        nrOfTrees = other.nrOfTrees;
        other.heapSize = 0;
        other.nrOfTrees = 0;
        other.first = other.last = other.minNode = nullptr;
        return;
    }
    last->next = other.first;
    other.first->prev = last;
    last = other.last;
    heapSize += other.heapSize;
    nrOfTrees += other.nrOfTrees;
    if (comp(other.minNode->val, minNode->val))
        minNode = other.minNode;
    other.heapSize = 0;
    other.nrOfTrees = 0;
    other.first = other.last = other.minNode = nullptr;
}

template<typename T, typename Comp>
void FibonacciHeap<T, Comp>::decreaseKey(DoublyLinkedNode<T>* node, T newVal) {
    if (!node)
        throw std::invalid_argument("Node is nullptr!");
    if (!comp(newVal, node->val))
        throw std::invalid_argument("New value is not smaller (in sense of comparator) than previous one!"); 
    node->val = newVal;
    if (comp(newVal, minNode->val))
        minNode = node;
    if (!(node->father)) {return;}
    DoublyLinkedNode<T>* father = node->father;
    if (!comp(newVal, father->val)) {return;}
    while (father->marked) {
        father->nrOfDirectChildren--;
        father->marked = false;
        if (father->leftChild == node)
            father->leftChild = node->next;
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        node->father = nullptr;
        node->next = nullptr;
        node->prev = last;
        last->next = node;
        last = node;
        nrOfTrees++;
        node = father;
        father = node->father;
    }
    if (father->father)
        father->marked = true;
    father->nrOfDirectChildren--;
    if (father->leftChild == node)
        father->leftChild = node->next;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    node->father = nullptr;
    node->next = nullptr;
    node->prev = last;
    last->next = node;
    last = node;
    nrOfTrees++;
}

template<typename T, typename Comp>
void FibonacciHeap<T, Comp>::deleteMin() {
    if (empty())
        throw std::logic_error("Heap is empty!");
    heapSize--;
    DoublyLinkedNode<T>* node = minNode;
    nrOfTrees += node->nrOfDirectChildren - 1;
    if (first == last) {
        if (!node->leftChild) {
            first = last = minNode = nullptr;
            delete node;
            return;
        }
        // node = last = first = minNode, node->next = node->prev = nullptr
        first = node->leftChild;
        node->leftChild = nullptr;
        delete node;
        last = first;
        while (last->next) {
            last->marked = false;
            last->father = nullptr;
            last = last->next;
        }
        last->marked = false;
        last->father = nullptr;
    }
    else {
        if (node->prev)
            node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
        if (first == node)
            first = node->next;
        if (last == node)
            last = node->prev;
        node->next = node->prev = nullptr;
        if (!node->leftChild)
            delete node;
        else {
            last->next = node->leftChild;
            node->leftChild->prev = last;
            last = node->leftChild;
            node->leftChild = nullptr;
            delete node;
            while (last->next) {
                last->marked = false;
                last->father = nullptr;
                last = last->next;
            }
            last->marked = false;
            last->father = nullptr;
        }
    }
    consolidate();
    minNode = node = first;
    while (node) {
        if (comp(node->val, minNode->val))
            minNode = node;
        node = node->next;
    }
}

template<typename T, typename Comp>
void FibonacciHeap<T, Comp>::removeMidRoot(DoublyLinkedNode<T>* root) {
    nrOfTrees--;
    root->prev->next = root->next;
    root->next->prev = root->prev;
    root->next = root->prev = nullptr;
}

template<typename T, typename Comp>
void FibonacciHeap<T, Comp>::addNodeAsAchild(DoublyLinkedNode<T>* d1, DoublyLinkedNode<T>* d2) {
    // Assumption: we add d1 to d2 as his child. d1 needs to be alone.
    d2->nrOfDirectChildren++;
    if (!d2->leftChild) {
        d2->leftChild = d1;
        return;
    }
    d2->leftChild->prev = d1;
    d1->next = d2->leftChild;
    d2->leftChild = d1;
    d1->father = d2;
}

template<typename T, typename Comp>
void FibonacciHeap<T, Comp>::consolidate() {
    // Note: It does not fix minNode!
    // Assumption: there is at least one element in the heap.
    DoublyLinkedNode<T> beforeFirst(first->val); // For convenience
    DoublyLinkedNode<T> afterLast(first->val); // For convenience
    beforeFirst.next = first;
    first->prev = &beforeFirst;
    afterLast.prev = last;
    last->next = &afterLast;
    std::vector<DoublyLinkedNode<T>*> different;
    DoublyLinkedNode<T>* node = first;
    while (node != &afterLast) {
        while (node->nrOfDirectChildren+1 >= different.size()) {
            different.push_back(nullptr);
        }
        DoublyLinkedNode<T>* node2 = node;
        node = node->next;
        while (different[node2->nrOfDirectChildren]) {
            DoublyLinkedNode<T>* d1 = different[node2->nrOfDirectChildren];
            different[node2->nrOfDirectChildren] = nullptr;
            DoublyLinkedNode<T>* d2 = node2;
            if (comp(d2->val, d1->val)) {
                removeMidRoot(d1);
                addNodeAsAchild(d1, d2);
                node2 = d2;
            }
            else {
                removeMidRoot(d2);
                addNodeAsAchild(d2, d1);
                node2 = d1;
            }
        }
        different[node2->nrOfDirectChildren] = node2;
        if (node->nrOfDirectChildren+1 == different.size()) {
            different.push_back(nullptr);
        }
    }
    first = beforeFirst.next;
    beforeFirst.next = first->prev = nullptr;
    last = afterLast.prev;
    afterLast.prev = last->next = nullptr;
}