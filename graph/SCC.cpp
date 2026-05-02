#include <bits/stdc++.h>
using namespace std;

#define ll long long

// adjList: الجراف الأصلي
// comps: كل SCC عبارة عن vector
// dagList: الجراف بعد الضغط (DAG)
vector<vector<int>> adjList, comps, dagList;

// inStack: هل node موجودة في الستاك؟
// lowLink, dfn: مستخدمين في Tarjan
// comp: رقم الـ component لكل node
// inDeg / outDeg: درجات الـ DAG
vector<int> inStack, lowLink, dfn, comp, inDeg, outDeg;

stack<int> stk;
int ndfn; // timer

// ================== TARJAN ==================
void tarjan(int node) {

    // أول ما ندخل node
    lowLink[node] = dfn[node] = ndfn++;

    inStack[node] = 1;
    stk.push(node);

    // نمشي على الجيران
    for (int ch : adjList[node]) {

        // لو لسه مزرناهوش
        if (dfn[ch] == -1) {
            tarjan(ch);

            // نحدث أقل reachable time
            lowLink[node] = min(lowLink[node], lowLink[ch]);
        } 

        // لو في stack → back edge
        else if (inStack[ch]) {
            lowLink[node] = min(lowLink[node], dfn[ch]);
        }
    }

    // لو node دي root بتاع SCC
    if (lowLink[node] == dfn[node]) {

        comps.push_back(vector<int>());

        while (true) {
            int x = stk.top();
            stk.pop();

            inStack[x] = 0;

            // حط node في الـ component الحالي
            comp[x] = (int)comps.size() - 1;
            comps.back().push_back(x);

            if (x == node) break;
        }
    }
}

// ================== BUILD SCC ==================
void buildSCC(int n) {

    // initialize
    inStack.assign(n, 0);
    lowLink.assign(n, 0);
    dfn.assign(n, -1);
    comp.assign(n, -1);

    while (!stk.empty()) stk.pop();

    comps.clear();
    ndfn = 0;

    // شغل Tarjan على كل node
    for (int i = 0; i < n; i++) {
        if (dfn[i] == -1)
            tarjan(i);
    }
}

// ================== BUILD DAG ==================
void buildDAG() {

    int csz = comps.size(); // عدد الـ SCC

    dagList.assign(csz, vector<int>());
    inDeg.assign(csz, 0);
    outDeg.assign(csz, 0);

    // set علشان نشيل duplicate edges
    set<pair<int,int>> edges;

    // لف على كل edge في الجراف الأصلي
    for (int i = 0; i < (int)adjList.size(); i++) {
        for (int j : adjList[i]) {

            // لو edge بين component مختلفين
            if (comp[i] != comp[j]) {
                edges.insert({comp[i], comp[j]});
            }
        }
    }

    // بناء DAG
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

      
        adjList.assign(n, vector<int>());

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;

            u--, v--; // zero-based

            adjList[u].push_back(v);
        }

        // 1) استخراج SCC
        buildSCC(n);

        // 2) تحويله إلى DAG
        buildDAG();

        int csz = comps.size();

        // لو كله component واحدة → already strongly connected
        if (csz == 1) {
            cout << 0 << "\n";
            continue;
        }

        int sources = 0, sinks = 0;

        // حساب عدد الـ sources و sinks في الـ DAG
        for (int i = 0; i < csz; i++) {
            if (inDeg[i] == 0) sources++;  // no incoming edges
            if (outDeg[i] == 0) sinks++;   // no outgoing edges
        }

        // أقل عدد edges لتحويله strongly connected
        cout << max(sources, sinks) << "\n";
    }

    return 0;
}
