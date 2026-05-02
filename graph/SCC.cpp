#include <bits/stdc++.h>
using namespace std;

#define ll long long

// adjList: original graph
// comps: list of SCCs (each component is a vector of nodes)
// dagList: compressed graph (DAG)
vector<vector<int>> adjList, comps, dagList;

// inStack: whether node is currently in stack
// lowLink, dfn: used in Tarjan algorithm
// comp: component id for each node
// inDeg / outDeg: degrees in the DAG
vector<int> inStack, lowLink, dfn, comp, inDeg, outDeg;

stack<int> stk;
int ndfn; // timer

// ================== TARJAN ==================
void tarjan(int node) {

    // initialize discovery time and low link
    lowLink[node] = dfn[node] = ndfn++;

    inStack[node] = 1;
    stk.push(node);

    // traverse neighbors
    for (int ch : adjList[node]) {

        // if not visited
        if (dfn[ch] == -1) {
            tarjan(ch);

            // update lowLink
            lowLink[node] = min(lowLink[node], lowLink[ch]);
        } 

        // back edge (node still in stack)
        else if (inStack[ch]) {
            lowLink[node] = min(lowLink[node], dfn[ch]);
        }
    }

    // if node is root of SCC
    if (lowLink[node] == dfn[node]) {

        comps.push_back(vector<int>());

        while (true) {
            int x = stk.top();
            stk.pop();

            inStack[x] = 0;

            // assign node to current component
            comp[x] = (int)comps.size() - 1;
            comps.back().push_back(x);

            if (x == node) break;
        }
    }
}

// ================== BUILD SCC ==================
void buildSCC(int n) {

    // initialize arrays
    inStack.assign(n, 0);
    lowLink.assign(n, 0);
    dfn.assign(n, -1);
    comp.assign(n, -1);

    while (!stk.empty()) stk.pop();

    comps.clear();
    ndfn = 0;

    // run Tarjan on all nodes
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1)
            tarjan(i);
    }
}

// ================== BUILD DAG ==================
void buildDAG() {

    int csz = comps.size(); // number of SCCs

    dagList.assign(csz, vector<int>());
    inDeg.assign(csz, 0);
    outDeg.assign(csz, 0);

    // use set to remove duplicate edges
    set<pair<int,int>> edges;

    // iterate over original edges
    for (int i = 0; i < (int)adjList.size(); i++) {
        for (int j : adjList[i]) {

            // edge between different components
            if (comp[i] != comp[j]) {
                edges.insert({comp[i], comp[j]});
            }
        }
    }

    // build DAG
    for (auto e : edges) {
        int u = e.first;
        int v = e.second;

        dagList[u].push_back(v);

        outDeg[u]++;
        inDeg[v]++;
    }
}

// ================== MAIN ==================
int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {

        int n, m;
        cin >> n >> m;

        // read graph
        adjList.assign(n, vector<int>());

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;

            u--, v--; // convert to 0-based

            adjList[u].push_back(v);
        }

        // 1) build SCC
        buildSCC(n);

        // 2) build compressed DAG
        buildDAG();

        int csz = comps.size();

        // if already one component → already strongly connected
        if (csz == 1) {
            cout << 0 << "\n";
            continue;
        }

        int sources = 0, sinks = 0;

        // count sources and sinks in DAG
        for (int i = 0; i < csz; i++) {
            if (inDeg[i] == 0) sources++;  // no incoming edges
            if (outDeg[i] == 0) sinks++;   // no outgoing edges
        }

        // minimum edges needed to make graph strongly connected
        cout << max(sources, sinks) << "\n";
    }

    return 0;
}
