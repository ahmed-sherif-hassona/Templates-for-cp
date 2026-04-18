#include <bits/stdc++.h>
using namespace std;
#define sherif ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
typedef long long ll;
typedef long double ld;
#define int ll
#define endl '\n'
const int mod = 1000000007;
const int N=1e5+5;
const int oo=4e18;

void solve() {
   int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>>adj(n,vector<int>(n,oo));
    for (int i=0;i<n;i++) {
        adj[i][i]=0;
    }
    while (m--) {
        int u,v,w;
        cin>>u>>v>>w;
        u--,v--;    //0-based
        adj[u][v]=min(w,adj[u][v]);//directed
    }
    for (int k=0;k<n;k++) {
        for (int i=0;i<n;i++) {
            for (int j=0;j<n;j++) {
                if (adj[i][k]<oo&&adj[k][j]<oo) {
                    adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
                }
            }
        }
    }
    while (q--) {
        int i,j;
        cin>>i>>j;
        i--,j--;   //0-based
        int ans=adj[i][j];
        if (ans==oo)
            cout<<-1<<endl;
        else
        cout<<ans<<endl;
    }
}
int32_t main() {
    sherif;
   //  freopen("lex.in", "r", stdin);
    // freopen("time.out", "w", stdout);
    int t=1;
   // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
