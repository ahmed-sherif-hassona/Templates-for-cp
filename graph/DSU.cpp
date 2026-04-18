
struct dsu {
    int sz;
    vector<int>parant,groub,mx,mn;
    dsu(int n) {
        sz=n;
        parant=vector<int>(n+1);
        groub=vector<int>(n+1,1);
        mx=vector<int>(n+1);
        mn=vector<int>(n+1);
        iota(parant.begin(),parant.end(),0);
        iota(mx.begin(),mx.end(),0);
        iota(mn.begin(),mn.end(),0);
    }
    int find(int node) {
        if (parant[node]==node)return node;
        return find(parant[node]);
    }
    void marge(int u,int v) {
        int leader1=find(u);
        int leader2=find(v);
        if (leader1==leader2)return;
        if (groub[leader1]>groub[leader2])swap(leader1,leader2);
        parant[leader1]=leader2;
        mx[leader2]=max(mx[leader1],mx[leader2]);
        mn[leader2]=min(mn[leader1],mn[leader2]);
        groub[leader2]+=groub[leader1];
    }
    bool samegroub(int u,int v) {
        return find(u)==find(v);
    }
    int getmin(int node) {
        return mn[find(node)];
    }
    int getmax(int node) {
        return mx[find(node)];
    }
    int getsize(int node) {
        return groub[find(node)];
    }

};
