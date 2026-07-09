struct BinaryTrie{
    struct Node{
        Node *child[2];
        int frq[2];
        Node(){
            child[0]=child[1]=0;
            frq[0]=frq[1]=0;
        }
    };
    BinaryTrie(){
        insert(0);
    }
    Node *root=new Node();
    void insert(int n)
    {
        Node *cur=root;
        for(int i=29;i>=0;i--)
        {
            bool idx=(n>>i)&1;
            if(cur->child[idx]==0) cur->child[idx]=new Node();
            cur->frq[idx]++;
            cur=cur->child[idx];
        }
    }
    void del(int n,int i,Node *cur)
    {
        if(i==-1)return;
        bool idx=(n>>i)&1;
        del(n,i-1,cur->child[idx]);
        cur->frq[idx]--;
        if(cur->frq[idx]==0)
        {
            delete cur->child[idx];
            cur->child[idx]=0;
        }
    }
    int MxXor(int n)
    {
        int ret=0;Node *cur=root;
        for(int i=29;i>=0;i--)
        {
            bool idx=(n>>i)&1;
            if(cur->child[idx^1]==0) cur=cur->child[idx];
            else cur=cur->child[idx^1],ret|=(1<<i);
        }
        return ret;
    }
};



//---------------------------------------------------------------------------------------

struct BinaryTrie {
    using ll = long long;

    struct Node {
        Node* child[2];
        int cnt;

        Node() {
            child[0] = child[1] = nullptr;
            cnt = 0;
        }
    };

    Node* root;
    int B;

    BinaryTrie(int bits = 60) {
        B = bits;
        root = new Node();
    }

    void insert(ll x) {
        Node* cur = root;

        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;

            if (!cur->child[b])
                cur->child[b] = new Node();

            cur = cur->child[b];
            cur->cnt++;
        }
    }

    void remove(ll x) {
        Node* cur = root;

        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;

            if (!cur->child[b])
                return;

            cur = cur->child[b];
            cur->cnt--;
        }
    }

    bool contains(ll x) {
        Node* cur = root;

        for (int i = B; i >= 0; i--) {
            int b = (x >> i) & 1;

            if (!cur->child[b] || cur->child[b]->cnt == 0)
                return false;

            cur = cur->child[b];
        }

        return true;
    }

    ll maxXor(ll x) {
        Node* cur = root;
        ll ans = 0;

        for (int i = B; i >= 0; i--) {

            int b = (x >> i) & 1;

            if (cur->child[b ^ 1] && cur->child[b ^ 1]->cnt > 0) {
                ans |= (1LL << i);
                cur = cur->child[b ^ 1];
            }
            else {
                cur = cur->child[b];
            }
        }

        return ans;
    }

    ll minXor(ll x) {
        Node* cur = root;
        ll ans = 0;

        for (int i = B; i >= 0; i--) {

            int b = (x >> i) & 1;

            if (cur->child[b] && cur->child[b]->cnt > 0) {
                cur = cur->child[b];
            }
            else {
                ans |= (1LL << i);
                cur = cur->child[b ^ 1];
            }
        }

        return ans;
    }

    ll kthXor(ll x, int k) {
        Node* cur = root;
        ll ans = 0;

        for (int i = B; i >= 0; i--) {

            int b = (x >> i) & 1;

            int same = 0;

            if (cur->child[b])
                same = cur->child[b]->cnt;

            if (same >= k) {
                cur = cur->child[b];
            } else {
                k -= same;
                ans |= (1LL << i);
                cur = cur->child[b ^ 1];
            }
        }

        return ans;
    }

    int countLessThanK(ll x, ll k) {
        Node* cur = root;
        int ans = 0;

        for (int i = B; i >= 0; i--) {

            if (!cur)
                break;

            int xb = (x >> i) & 1;
            int kb = (k >> i) & 1;

            if (kb) {

                if (cur->child[xb])
                    ans += cur->child[xb]->cnt;

                cur = cur->child[xb ^ 1];

            } else {

                cur = cur->child[xb];

            }
        }

        return ans;
    }

    ll maxSubarrayXor(vector<ll>& a) {
        BinaryTrie trie(B);

        trie.insert(0);

        ll pref = 0;
        ll ans = 0;

        for (ll x : a) {
            pref ^= x;
            ans = max(ans, trie.maxXor(pref));
            trie.insert(pref);
        }

        return ans;
    }
};
