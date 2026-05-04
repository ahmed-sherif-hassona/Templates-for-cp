#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m;

vector<vector<pair<int,int>>> adj; 
// adj[u] = {v, edge_id}

vector<int> deg;      // out - in
vector<int> visEdge;

vector<int> nodes, edges;

bool EulerPathDir() {
    int st = -1, en = -1, cand = 1;

    for (int u = 1; u <= n; u++) {
        if (abs(deg[u]) > 1) return false;
        if (!adj[u].empty()) cand = u;

        if (deg[u] == 1) {
            if (st != -1) return false;
            st = u;
        }

        if (deg[u] == -1) {
            if (en != -1) return false;
            en = u;
        }
    }

    if (st == -1) st = cand;

    nodes.clear();
    edges.clear();
    visEdge.assign(m + 1, 0);

    function<void(int)> dfs = [&](int u) {
        while (!adj[u].empty()) {
            auto [v, id] = adj[u].back();
            adj[u].pop_back();

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
        deg[u]++;   // out
        deg[v]--;   // in
    }

    if (EulerPathDir()) {
        // ✔ print nodes
        cout << "Nodes path:\n";
        for (auto v : nodes)
            cout << v << " ";
        cout << "\n";

        // ✔ print edges
        cout << "Edges path:\n";
        for (auto e : edges)
            cout << e << " ";
        cout << "\n";
    } 
    else {
        cout << "NO EULER PATH\n";
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
