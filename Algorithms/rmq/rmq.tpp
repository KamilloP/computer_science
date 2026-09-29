template<typename T, typename Comp>
RMQ<T, Comp>::RMQ(const std::vector<T>& seq, Comp c):msb({-1}), powers2({1}), comp(c) {
    const int N = int(seq.size());
    if (N==0)
        throw std::invalid_argument("RMQ(const std::vector<T>& seq, Comp c = Comp{}): seq is empty");

    int pow2=1, logN=0; // logN = floor(log_2(N))
    for (int i=1; i<=N; i++) {
        if (i >= 2*pow2) {
            pow2 *= 2;
            powers2.push_back(pow2);
            logN++;
        }
        msb.push_back(logN);
    }

    std::vector<int> current;
    for (int i=0; i<N; i++)
        current.push_back(i);
    rmq.push_back(current); // copy
    current.clear();
    
    for (int i=1; i<=logN; i++) {
        for (int j=0; j+powers2[i]<=N; j++) {
            if (comp(seq[rmq[i-1][j]], seq[rmq[i-1][j+powers2[i-1]]])) {
                current.push_back(rmq[i-1][j]);
            }
            else {
                current.push_back(rmq[i-1][j+powers2[i-1]]);
            }
        }
        rmq.push_back(current);
        current.clear();
    }
}

template<typename T, typename Comp>
int RMQ<T, Comp>::argmin(int i, int j, const std::vector<T>& seq) const {
    if (i<0 || i>j || j>= int(rmq[0].size())) {
        throw std::invalid_argument("RMQ<T, Comp>::query(int i, int j): arguments out of bound");
    }
    int logN = msb[j-i+1];
    int r = j-powers2[logN]+1;
    if (comp(seq[rmq[logN][j]], seq[rmq[logN][r]]))
        return rmq[logN][i];
    return rmq[logN][r];
}