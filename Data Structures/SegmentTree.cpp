#include <bits/stdc++.h>
using namespace std;
#define sherif ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
typedef long long ll;
typedef long double ld;
#define int ll
#define endl '\n'
const int mod = 1000000007;
int oo = 1e18;
struct node {
    int sum;
    node()
    {
        sum=0;
    }
    node(int x)
    {
        sum=x;
    }
    void change(int x)
    {
        sum=x;
    }
};

struct segtree
{
    int tree_size;
    vector<node>segdata;

    segtree (int n)
    {
        tree_size=1;
        while(tree_size<n)tree_size*=2;
        segdata.assign(2*tree_size,node());
    }

    node marge(node &lf,node &ri) {
        node ans=node();
        ans.sum=lf.sum+ri.sum;
        return ans;
    }

    void set(int idx,int val,int ni,int lx,int rx) {

        if (rx-lx==1) {
            segdata[ni].change(val);
            return;
        }
        int mid=(lx+rx)/2;
        if (idx<mid) {
            set(idx,val,ni*2+1,lx,mid);
        }
        else {
            set(idx,val,ni*2+2,mid,rx);
        }
        segdata[ni]=marge(segdata[2*ni+1],segdata[2*ni+2]);
    }

    void set(int idx,int val ) {
        set(idx,val,0,0,tree_size);
    }

    node get(int l,int r,int ni,int lx,int rx) {

        if (lx>=l&&rx<=r)
            return segdata[ni];
        if (lx>=r||rx<=l)
            return node();
        int mid=(rx+lx)/2;

        node lf=get(l,r,2*ni+1,lx,mid);
        node ri=get(l,r,2*ni+2,mid,rx);
        return marge(lf,ri);
    }

    int get(int l,int r) {
        return get(l,r,0,0,tree_size).sum;
    }
};

void solve() {

    int n,q;
    cin>>n>>q;
    vector<int>arr(n);
    segtree st=segtree(n);
    for (int i=0;i<n;i++) {
        cin>>arr[i];
        st.set(i,arr[i]);
    }

    while (q--) {
        int flag,l,r;
        cin>>flag>>l>>r;
        if (flag==1)
            st.set(l,r);
        else {
            cout<<st.get(l,r)<<endl;
        }
    }


}
int32_t main() {
    sherif;

    int t=1;
  //  cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
