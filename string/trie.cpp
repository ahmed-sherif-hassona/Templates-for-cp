struct Trie{
    struct Node{
        Node*child[26];
        int IsEnd,Prefix;
        Node(){
            memset(child,0,sizeof child);
            IsEnd=Prefix=0;
        }
    };
    Node*root=new Node();
    void insert(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';
            if(cur->child[idx]==0)
            {
                cur->child[idx]=new Node();
            }
            cur=cur->child[idx];
            cur->Prefix++;
        }
        cur->IsEnd++;
    }
    bool SearchWord(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';
            if(cur->child[idx]==0)return 0;
            cur=cur->child[idx];
        }
        return cur->IsEnd;
    }
    int CountWord(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';
            if(cur->child[idx]==0)return 0;
            cur=cur->child[idx];
        }
        return cur->IsEnd;
    }
    int CountPrefix(string &s)
    {
        Node*cur=root;
        for(auto it:s)
        {
            int idx=it-'a';
            if(cur->child[idx]==0)return 0;
            cur=cur->child[idx];
        }
        return cur->Prefix;
    }
};


//----------------------------------------------------------------------------------------------


struct Trie {

    struct Node {
        Node* child[26];
        int Prefix, IsEnd, depth;

        Node(int d = 0) {
            memset(child, 0, sizeof child);
            Prefix = IsEnd = 0;
            depth = d;
        }
    };

    Node* root = new Node();

    multiset<int> level[N];

    void insert(const string &s)
    {
        Node* cur = root;

        for (int i = 0; i < (int)s.size(); i++)
        {
            int idx = s[i] - 'a';

            if (!cur->child[idx])
            {
                cur->child[idx] = new Node(i + 1);
                level[i + 1].insert(0);
            }

            cur = cur->child[idx];

            level[cur->depth].erase(level[cur->depth].find(cur->Prefix));
            cur->Prefix++;
            level[cur->depth].insert(cur->Prefix);
        }

        cur->IsEnd++;
    }

    void erase(const string &s)
    {
        Node* cur = root;

        for (int i = 0; i < (int)s.size(); i++)
        {
            int idx = s[i] - 'a';

            cur = cur->child[idx];

            level[cur->depth].erase(level[cur->depth].find(cur->Prefix));
            cur->Prefix--;
            level[cur->depth].insert(cur->Prefix);
        }

        cur->IsEnd--;
    }

    int MaxPrefixAtDepth(int d)
    {
        if (level[d].empty()) return 0;
        return *level[d].rbegin();
    }
};
