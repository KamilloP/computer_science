#ifndef __FIB_HEAP_H__
#define __FIB_HEAP_H__

#include<functional>
#include<stdexcept>
#include<vector>


template<typename T>
class DoublyLinkedNode {
public:
    DoublyLinkedNode<T>* father;
    DoublyLinkedNode<T>* leftChild;
    DoublyLinkedNode<T>* next;
    DoublyLinkedNode<T>* prev;
    T val;
    bool marked;
    int nrOfDirectChildren;
    // std::vector<DoublyLinkedNode*> degreeRepresentants; // logn max
    DoublyLinkedNode(T v):
        father(nullptr),
        leftChild(nullptr), 
        next(nullptr),
        prev(nullptr),
        val(v),
        marked(false),
        nrOfDirectChildren(0)  {}
    ~DoublyLinkedNode() {
        if (leftChild) {delete leftChild;}
        if (next) {delete next;}
    }
};

template<typename T, typename Comp = std::less<T>>
class FibonacciHeap {
private:
    const Comp comp;
    DoublyLinkedNode<T>* first;
    DoublyLinkedNode<T>* last;
    DoublyLinkedNode<T>* minNode;
    int nrOfTrees;
    int heapSize;
    void consolidate();
    void addNodeAsAchild(DoublyLinkedNode<T>* d1, DoublyLinkedNode<T>* d2);
    void removeMidRoot(DoublyLinkedNode<T>* root);
public:
    FibonacciHeap(Comp c = Comp{}):
        comp(c), 
        first(nullptr),
        last(nullptr),
        minNode(nullptr),
        nrOfTrees(0),
        heapSize(0) {}
    ~FibonacciHeap() {delete first;}
    int size() const {return heapSize;}
    bool empty() const {return heapSize == 0;}
    T minVal() const;
    void merge(FibonacciHeap<T, Comp>& other); // We assume other.comp = comp
    DoublyLinkedNode<T>* insert(T val);
    void deleteMin();
    void decreaseKey(DoublyLinkedNode<T>* node, T newVal);
};

#include "fib_heap.tpp"

#endif