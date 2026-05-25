struct AC {
    int N, P;
    const int A = 26;
    //next: at each node where to fail when we put any char
    vector <vector <int>> next;
    //link: at each node where is the max proper suffix i can match
    // out link: at each node where is the max proper suffix i can match that has a pattern
    vector <int> link, out_link;

    // out: at each node (vector of indexes of pattern)
    vector <vector <int>> out;
    AC(): N(0), P(0) {node();}
    int node() {
        next.emplace_back(A, 0);
        link.emplace_back(0);
        out_link.emplace_back(0);
        out.emplace_back(0);
        return N++;
    }
    inline int get (char c) {
        return c - 'a';
    }
    void add_pattern (const string T, int idx) {
        int u = 0;
        for (auto c : T) {
            if (!next[u][get(c)]) next[u][get(c)] = node();
            u = next[u][get(c)];
        }
        out[u].push_back(idx);
    }
    void compute() {
        queue <int> q;
        for (q.push(0); !q.empty();) {
            int u = q.front(); q.pop();
            for (int c = 0; c < A; ++c) {
                int v = next[u][c];
                if (!v) next[u][c] = next[link[u]][c];
                else {
                    link[v] = u ? next[link[u]][c] : 0;
                    out_link[v] = out[link[v]].empty() ? out_link[link[v]] : link[v];
                    q.push(v);
                }
            }
        }
    }
    int advance (int u, char c) {
        while (u && !next[u][get(c)]) u = link[u];
        u = next[u][get(c)];
        return u;
    }
    string smallest(int L){
        string res;
        int u = 0;
        for (int i = 0;i < L;i++){
            for (int c = 0;c < 26;c++){
                int v = next[u][c];
                if (out[v].empty()){
                    res.push_back(char('a' + c));
                    u = v;
                    break;
                }
            }
        }
        return res;
    }

   string smallest_all(int P) {

    int FULL = (1 << P) - 1;

    vector<vector<int>> vis(N, vector<int>(1 << P, 0));

    struct State {
        int node, mask;
    };

    queue<State> q;

    vector<vector<pair<int,int>>> par(
        N,
        vector<pair<int,int>>(1 << P, {-1,-1})
    );

    vector<vector<char>> pc(
        N,
        vector<char>(1 << P)
    );

    q.push({0,0});
    vis[0][0] = 1;

    while (!q.empty()) {

        auto [u, mask] = q.front();
        q.pop();

        if (mask == FULL) {

            string res;

            while (!(u == 0 && mask == 0)) {
                res.push_back(pc[u][mask]);

                auto p = par[u][mask];

                u = p.first;
                mask = p.second;
            }

            reverse(res.begin(), res.end());

            return res;
        }

        for (int c = 0; c < 26; c++) {

            int v = next[u][c];

            int nmask = mask;

            for (auto id : out[v])
                nmask |= (1 << id);

            int x = out_link[v];

            while (x) {
                for (auto id : out[x])
                    nmask |= (1 << id);

                x = out_link[x];
            }

            if (!vis[v][nmask]) {

                vis[v][nmask] = 1;

                par[v][nmask] = {u, mask};

                pc[v][nmask] = char('a' + c);

                q.push({v, nmask});
            }
        }
    }

    return "";  
}
};
