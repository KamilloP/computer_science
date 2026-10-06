
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include<string>
#include<vector>
#include<stdexcept>
#include<utility>
#include<algorithm>
#include<queue>
#include<optional>

#include "../rmq/rmq.h"

using Graph = std::tuple<int, int, std::vector<std::vector<int>>>;

bool isProperTree(const Graph& graph); 

std::vector<int> findIndorder(int root, const Graph& graph);

std::vector<int> findHeight(int root, const Graph& graph);

class LCA {
private:
    int bucketSize; // B = bucketSize = 1/2 * logN
    int V;
    std::vector<int> inorder; // N=2*V-1
    std::vector<int> height; // V
    std::vector<int> firstOccurence; // V 
    std::vector<std::vector<std::vector<int>>> bruteRMQForRepresentant; /*
        2^{B-1} \approx \sqrt{n} representants, for each of them brute RMQ 
        Each representant has encoding of B-1 bits because starting from relative height `0`
        we increase or decrease height by one (B-1) times. Of course bucket size is B and we 
        compute quadratic RMQ for B^2 quries for given representant. 
    */
    std::vector<int> beginOfBucket; // \ceil{N/B}
    std::vector<unsigned int> representant; // \ceil{N/B}
    std::vector<unsigned int> bucketNr; // N
    std::vector<int> arange; // \ceil{N/B}. It is an arr in rmq, we have to pass it to rmq->argmin.
    
    int computeHeight(int bucket) const;

    struct LCAComparator {
        const LCA* lca;
        LCAComparator(const LCA& lca) : lca(&lca) {}
        bool operator()(int a, int b) const {
            // `a` and `b` are number of buckets
            return lca->computeHeight(a) < lca->computeHeight(b);
        }
    };
    std::optional<RMQ<int, LCAComparator>> rmq;

    ///////////////////////////////////////////////////////////
    // Auxilliary functions ///////////////////////////////////
    ///////////////////////////////////////////////////////////
    std::vector<std::vector<int>> computeQuadraticRMQ(const std::vector<int>& relativeHeights);
    
    void computeBruteForRepresentant(
        int nrOfBitsRemaining,
        std::vector<int>& relativeHeights
    );

    int suffixMin(int pos) const;
    int prefixMin(int pos) const;
    int middleMin(int bucketU, int bucketV) const;

public:
    LCA(int root, const Graph& tree);
    ~LCA() {}
    int lca(int u, int v) const;

    std::vector<int> getInorder() const {return inorder;}
    std::vector<int> getHeight() const {return height;}
    std::vector<int> getFirstOccurence() const {return firstOccurence;}
    std::vector<int> getBeginOfBucket() const {return beginOfBucket;}
    std::vector<unsigned int> getRepresentant() const {return representant;}
    std::vector<unsigned int> getBucketNr() const {return bucketNr;}
};

#include "graph.tpp"
#include "lca.tpp"

#endif