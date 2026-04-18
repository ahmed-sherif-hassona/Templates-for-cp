#include <bits/stdc++.h>
using namespace std;
#define sherif ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
typedef long long ll;
typedef long double ld;
#define int ll
#define endl '\n'
const int mod = 1000000007;
const int N=1e5+5;
int n,m,ans,cost[N],vis[N],color[N];
vector<int>adj[N];
vector<int>perant(N,-1);
vector<vector<int>>res;
int bfs(int start,int end) {
    queue<pair<int,int>>q;
    q.push({start,0});
    color[start]=1;
    vis[start]=1;
    while(!q.empty())
    {
        pair<int,int>p=q.front();
        q.pop();
        int node=p.first, cost=p.second;
        for(auto it:adj[node])
        {
            if(!vis[it])
            {
                vis[it]=1;
                perant[it]=node;
                q.push({it,cost+1});
                color[it]=3-color[node];
            }
            else {
                if (color[it]==color[node])
                    return false;
            }
        }
    }
    return true;
}
void solve() {
    cin>>n>>m;
    for (int i=0;i<m;i++) {
        int  u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int flag=1;
    for (int i=1;i<=n;i++) {
        if (!vis[i])
            flag&=bfs(i,n);
    }
    if (flag) {
        for (int i=1;i<=n;i++) {
            cout<<color[i]<<" ";
        }
    }
    else
        cout<<"IMPOSSIBLE"<<endl;
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
