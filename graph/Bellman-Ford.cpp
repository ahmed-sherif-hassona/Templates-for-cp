#include <bits/stdc++.h>
using namespace std;

#define int long long
const long long INF = 1e18;
#define N 1003

int vis1[N], vis2[N];
vector<int> adj1[N], adj2[N];

void dfs(int i) {
    vis1[i] = 1;
    for (auto it : adj1[i]) {
        if (!vis1[it]) dfs(it);
    }
}

void dfs2(int i) {
    vis2[i] = 1;
    for (auto it : adj2[i]) {
        if (!vis2[it]) dfs2(it);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> x(m), y(m), z(m);

    for (int i = 1; i <= n; i++) {
        adj1[i].clear();
        adj2[i].clear();
        vis1[i] = vis2[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i] >> z[i];
        adj1[x[i]].push_back(y[i]);
        adj2[y[i]].push_back(x[i]);
    }

    vector<int> cost(n + 1, INF);
    vector<int> cycle(n + 1, 0);

    cost[1] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int u = x[j], v = y[j], w = z[j];

            if (cost[u] != INF && cost[u] + w < cost[v]) {
                cost[v] = cost[u] + w;
                if (i == n - 1) {
                    cycle[v] = 1;
                }
            }
        }
    }

    dfs(1);
    dfs2(n);

    for (int i = 1; i <= n; i++) {
        if (cycle[i] && vis1[i] && vis2[i]) {
            cout << "-inf\n"; // negative cycle affecting path
            return;
        }
    }

    cout << cost[n] << endl;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
