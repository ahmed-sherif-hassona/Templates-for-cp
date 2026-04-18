#include <bits/stdc++.h>
using namespace std;
#define sherif ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
typedef long long ll;
typedef long double ld;
#define int ll
#define endl '\n'
const int mod = 1000000007;
const int N=1e5+5;
int n,m,ans,cost[N],vis[N],color[N],indegree[N];
vector<int>adj[N];
vector<int>perant(N,-1);
queue<int>topo;
void bfs(int start) {
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i=1;i<=n;i++) {
        if (!indegree[i]) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int cur=q.top();
        q.pop();
        topo.push(cur);
        for (auto ch:adj[cur]) {
            if (!vis[ch]) {
                indegree[ch]--;
                if (!indegree[ch]) {
                    vis[ch]=1;
                    q.push(ch);
                }
            }
        }
    }

}
void solve() {
    cin>>n>>m;
    for (int i=0;i<m;i++) {
        int  u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    bfs(1);
    if (topo.size()!=n) {
      cout<<"Sandro fails.";
      return;
     }
    for (int i=0;i<n;i++) {
        int x=topo.front();
        topo.pop();
        cout<<x<<" ";
    }
}
int32_t main() {
    sherif;
    int t=1;
    //cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
