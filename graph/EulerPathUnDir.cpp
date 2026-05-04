#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m;

vector<vector<pair<int,int>>> adj;
vector<int> deg;
vector<int> visEdge;

vector<int> nodes, edges;

bool EulerPathUndir() {
    int st = -1, en = -1, cand = 1;

    for (int u = 1; u <= n; u++) {
        if (!adj[u].empty()) cand = u;

        if (deg[u] % 2) {
            if (st == -1) st = u;
            else if (en == -1) en = u;
            else return false;
        }
    }

    if (st == -1) st = cand;
    else if (en == -1 && st != -1) en = st;

    nodes.clear();
    edges.clear();
    visEdge.assign(m + 1, 0);

    vector<int> ptr(n + 1, 0);

    function<void(int)> dfs = [&](int u) {
        while (ptr[u] < (int)adj[u].size()) {
            auto [v, id] = adj[u][ptr[u]++];

            if (visEdge[id]) continue;
            visEdge[id] = 1;

            dfs(v);

            edges.push_back(id);
            nodes.push_back(v);
        }
    };

    dfs(st);

    if ((int)edges.size() != m) return false;

    nodes.push_back(st);

    reverse(nodes.begin(), nodes.end());
    reverse(edges.begin(), edges.end());

    return true;
}

void solve() {
    cin >> n >> m;

    adj.assign(n + 1, {});
    deg.assign(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back({v, i});
        adj[v].push_back({u, i});

        deg[u]++;
        deg[v]++;
    }

    if (EulerPathUndir()) {
        cout << "Nodes:\n";
        for (auto v : nodes) cout << v << " ";
        cout << "\nEdges:\n";
        for (auto e : edges) cout << e << " ";
        cout << "\n";
    } else {
        cout << "NO EULER PATH\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
