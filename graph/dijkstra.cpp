#include <bits/stdc++.h>
using namespace std;
#define sherif ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
typedef long long ll;
typedef long double ld;
#define int ll
#define endl '\n'
const int mod = 1000000007;
const int N=1e5+5;
const int oo=LLONG_MAX;
int n,m;
vector<int>cost,vis,parant;
vector<pair<int,int>>adj[N];
void dijkstra(int st) {
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    pq.push({0,st});
    parant[st]=-1;
    cost[st]=0;
    while (!pq.empty()) {
        pair<int,int>p=pq.top();
        pq.pop();
        int node=p.second,dis=p.first;
        if (vis[node])continue;
        vis[node]=1;
        for (auto [a,b]:adj[node]) {
            if (cost[a]>cost[node]+b) {
                cost[a]=cost[node]+b;
                pq.push({cost[a],a});
                parant[a]=node;
            }
        }
    }

}
