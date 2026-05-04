int far_node, max_dist;
vector<int> parent;
void dfs(int v, int p, int d, vector<vector<int>> &adj) {
    parent[v] = p;

    if (d > max_dist) {
        max_dist = d;
        far_node = v;
    }

    for (int u : adj[v]) {
        if (u == p) continue;
        dfs(u, v, d + 1, adj);
    }
}

//  (start, end, distance)
tuple<int,int,int> tree_diameter(int n, vector<vector<int>> &adj) {
    parent.assign(n + 1, -1);

    // 1st DFS → A
    max_dist = -1;
    dfs(1, -1, 0, adj);
    int A = far_node;

    // 2nd DFS → B
    parent.assign(n + 1, -1);
    max_dist = -1;
    dfs(A, -1, 0, adj);
    int B = far_node;

    // reconstruct path if needed (optional)
    return {A, B, max_dist};
}
