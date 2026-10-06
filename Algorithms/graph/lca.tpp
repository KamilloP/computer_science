std::vector<std::vector<int>> LCA::computeQuadraticRMQ(const std::vector<int>& relativeHeights) {
    int B = relativeHeights.size();
    std::vector<int> empty;
    std::vector<std::vector<int>> result(B, empty);
    for (int i=0; i<B; i++) {
        int lastMin = INT_MAX, lastPos=-1;
        for (int j=i; j<B; j++) {
            if (relativeHeights[j] < lastMin) {
                lastMin = relativeHeights[j];
                lastPos = j;
            }
            result[i].push_back(lastPos);
        }
    }
    return result;
}

void LCA::computeBruteForRepresentant(
    int nrOfBitsRemaining,
    std::vector<int>& relativeHeights
) {
    // Assumption: at the beginning relativeHeights is {0}.
    if (nrOfBitsRemaining == 0) {
        bruteRMQForRepresentant.push_back(computeQuadraticRMQ(relativeHeights));
        return;
    }
    int h = relativeHeights[relativeHeights.size()-1];
    relativeHeights.push_back(h-1);
    computeBruteForRepresentant(nrOfBitsRemaining-1, relativeHeights);
    relativeHeights[relativeHeights.size()-1] = h+1;
    computeBruteForRepresentant(nrOfBitsRemaining-1, relativeHeights);
    relativeHeights.pop_back();
}

LCA::LCA(int root, const Graph& tree) {
    // Assumes `tree` is proper tree.
    // Assumes N >= 2, to satisfy this it is enough if V >= 2 (we want bucketSize >= 1).
    const auto& [V_, E, edges] = tree;
    V = V_;
    // std::cout << "V=" << V << "\n";
    inorder = findIndorder(root, tree);
    // std::cout << "Inorder done!\n"; 
    height = findHeight(root, tree);
    // std::cout << "Height done!\n"; 
    int N=inorder.size();
    // std::cout << "N=" << N << "\n";
    firstOccurence = std::vector<int>(V, INT_MAX);
    for (int i=0; i < N; i++) {
        firstOccurence[inorder[i]] = std::min(i, firstOccurence[inorder[i]]);
    }
    // std::cout << "FirstOccurence done!\n"; 
    bucketSize = 0;
    int pow2=1;
    while (pow2*pow2 < N) {
        pow2 *= 2;
        bucketSize++;
    }
    // std::cout << "Bucket size =" << bucketSize << "!\n";
    std::vector<int> relativeHeights {0};
    computeBruteForRepresentant(bucketSize-1, relativeHeights);
    // std::cout << "ComputeBruteForRepresentant done!\n";
    beginOfBucket.push_back(0);
    while (beginOfBucket[beginOfBucket.size()-1] + bucketSize < N) {
        beginOfBucket.push_back(beginOfBucket[beginOfBucket.size()-1] + bucketSize);
    }
    // std::cout << "BeginOfBucket done!\n"; 
    for (int i=0; i < int(beginOfBucket.size()); i++) {
        bucketNr.push_back(i);
        unsigned int representation = 0;
        int b = beginOfBucket[i];
        int j=b+1;
        while (j < std::min(b+bucketSize, N)) {
            bucketNr.push_back(i);
            representation *= 2;
            representation += height[inorder[j]] > height[inorder[j-1]] ? 1 : 0;
            j++;
        }
        while (j < b+bucketSize) {
            // Will execute only for the last bucket potentially.
            representation *= 2;
            representation += 1;
            j++;
        }
        representant.push_back(representation);
    }
    // std::cout << "BucketNr and representant done!\n"; 
    LCAComparator comp(*this);
    // std::cout << "LCAComparator done!\n";
    arange.reserve(beginOfBucket.size());
    for (int i=0; i<int(beginOfBucket.size()); i++) {arange.push_back(i);}
    // std::cout << "Arange done!\n";
    rmq.emplace(arange, comp);
    // std::cout << "RMQ done!\n";
}

int LCA::computeHeight(int bucket) const {
    int pos = beginOfBucket[bucket] + 
        bruteRMQForRepresentant[representant[bucket]][0][bucketSize-1];
    return height[inorder[pos]];
}

int LCA::suffixMin(int pos) const {
    unsigned int bucket = bucketNr[pos];
    int r = pos - beginOfBucket[bucket];
    int posSuffix = beginOfBucket[bucket] +
        bruteRMQForRepresentant[representant[bucket]][r][bucketSize-r-1];
    return inorder[posSuffix];
}

int LCA::prefixMin(int pos) const {
    unsigned int bucket = bucketNr[pos];
    int r = pos - beginOfBucket[bucket];
    int posPrefix = beginOfBucket[bucket] +
        bruteRMQForRepresentant[representant[bucket]][0][r];
    return inorder[posPrefix];
}

int LCA::middleMin(int bucketU, int bucketV) const {
    int minBucket = rmq->argmin(bucketU+1, bucketV-1, arange);
    int pos = beginOfBucket[minBucket] + 
        bruteRMQForRepresentant[representant[minBucket]][0][bucketSize-1];
    return inorder[pos];
}

int LCA::lca(int u, int v) const {
    int posU = firstOccurence[u], posV = firstOccurence[v];
    if (posU > posV) {std::swap(posU, posV);}
    unsigned int bucketU = bucketNr[posU], bucketV = bucketNr[posV];
    if (bucketU == bucketV) {
        int rU = posU - beginOfBucket[bucketU];
        int rV = posV - posU;
        int pos = beginOfBucket[bucketU] + 
            bruteRMQForRepresentant[representant[bucketU]][rU][rV];
        return inorder[pos];
    }
    if (bucketV == bucketU+1) {
        int suffix = suffixMin(posU), prefix = prefixMin(posV);
        if (height[suffix] < height[prefix])
            return suffix;
        else
            return prefix;
    }
    // bucketV > bucketU+1
    int suffix = suffixMin(posU), prefix = prefixMin(posV), middle = middleMin(bucketU, bucketV);
    if (height[suffix] > height[prefix]) {std::swap(suffix, prefix);}
    if (height[suffix] < height[middle]) {
        return suffix;
    }
    return middle;
}