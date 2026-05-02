#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef long double ld;
#define int ll
typedef tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
#define sherif ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define endl '\n'
const int mod = 1000000007;
const int N=5007;
const int oo=4e18;
vector<int> vis,low,dep;
vector<vector<int>>adj;
vector<pair<int,int>>ans;
bool bridge=false;
int timer=0;
void dfs(int v,int p) {
    vis[v]=1;
    low[v]=dep[v]=timer++;

    for (auto u:adj[v]) {

        if (u==p)
            continue;
        if (vis[u]) {
            //back edge;
            low[v]=min(low[v],dep[u]);
            if (dep[u]<dep[v]) {
                ans.push_back({u,v});
            }
        }
        else {
            //tree edge
            ans.push_back({u,v});
            dfs(u,v);
            low[v]=min(low[v],low[u]);
            if (low[u]>dep[v]) {
                // this is a bridge
                bridge=true;
            }

        }
    }
}
void solve() {
    int n,m;
    cin>>n>>m;
    vis.resize(n+1);
    low.resize(n+1);
    dep.resize(n+1);
    adj.resize(n+1);
    for (int i=0;i<m;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,-1);
    if (bridge) {
        cout<<0<<endl;
    }else {
        for (auto [u,v]:ans) {
            cout<<u<<" "<<v<<endl;
        }
    }

}
int32_t main() {
    sherif;
    //  freopen("lex.in", "r", stdin);
    // freopen("time.out", "w", stdout);


    int t=1;
    //  cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
