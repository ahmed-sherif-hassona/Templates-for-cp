struct FenwickTree {
    vector<int> bit;
    int n;
    FenwickTree(int n) {
        this->n = n;
        bit.assign(n + 1, 0);
    }
    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            bit[idx] += val;
        }
    }
    int query(int idx) {
        int ret = 0;
        for (; idx > 0; idx -= idx & -idx) {
            ret += bit[idx];
        }
        return ret;
    }
    int range(int l, int r) {
        return query(r) - query(l - 1);
    }
};
