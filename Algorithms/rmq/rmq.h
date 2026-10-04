/*
Range Minimum Query implementation.
Complexity (let N be length of the sequence):
- Preprocessing:
-- Time: O(NlogN)
-- Memory: O(NlogN)
- Answering each query (online): time and memory O(1).
*/

#ifndef __RMQ_H__
#define __RMQ_H__

#include <vector>
#include <functional>
#include <stdexcept>

template<typename T, typename Comp = std::less<T>>
class RMQ {
private:
    std::vector<std::vector<int>> rmq;
    std::vector<int> msb; // most significant set bit - on what position to search, logN.
    std::vector<int> powers2;
    const Comp comp;
public:
    RMQ(const std::vector<T>& seq, Comp c = Comp{});
    ~RMQ() {}
    std::vector<std::vector<int>> getRMQ() const {return rmq;}
    std::vector<int> getMSB() const {return msb;}
    std::vector<int> getPowers2() const {return powers2;}
    int argmin(int i, int j, const std::vector<T>& seq) const; /*
        We could theoretically copy whole vector with its values,
        but it would increase memory.
        We could remember reference or pointer to sequence,
        but if sequence would be destructed then we would end up
        with dangling pointer.
        Thus I chose the third option - we need reference to
        sequence with the same values as original in `min`. Otherwise
        undefined behaviour.
    */
};

#include "rmq.tpp"
/*
https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
*/

#endif