const int N = 1e5 + 5;

struct Trie{

    multiset<int> level[N];

    struct Node{

        Node* child[26];

        int IsEnd, Prefix, depth;

        Node(int d = 0){

            memset(child, 0, sizeof child);

            IsEnd = Prefix = 0;

            depth = d;
        }
    };

    Node* root = new Node();

    void insert(string &s)
    {
        Node* cur = root;

        for(int i = 0; i < s.size(); i++)
        {
            int idx = s[i] - 'a';

            if(cur->child[idx] == 0)
            {
                cur->child[idx] = new Node(i + 1);

                level[i + 1].insert(0);
            }

            cur = cur->child[idx];

            level[cur->depth].erase(
                level[cur->depth].find(cur->Prefix)
            );

            cur->Prefix++;

            level[cur->depth].insert(cur->Prefix);
        }

        cur->IsEnd++;
    }

    bool SearchWord(string &s)
    {
        Node* cur = root;

        for(auto it : s)
        {
            int idx = it - 'a';

            if(cur->child[idx] == 0)
                return 0;

            cur = cur->child[idx];
        }

        return cur->IsEnd;
    }

    int CountWord(string &s)
    {
        Node* cur = root;

        for(auto it : s)
        {
            int idx = it - 'a';

            if(cur->child[idx] == 0)
                return 0;

            cur = cur->child[idx];
        }

        return cur->IsEnd;
    }

    int CountPrefix(string &s)
    {
        Node* cur = root;

        for(auto it : s)
        {
            int idx = it - 'a';

            if(cur->child[idx] == 0)
                return 0;

            cur = cur->child[idx];
        }

        return cur->Prefix;
    }

    bool IsEmpty(Node* node)
    {
        for(int i = 0; i < 26; i++)
        {
            if(node->child[i])
                return false;
        }

        return true;
    }

    bool Delete(Node* cur, string &s, int depth = 0)
    {
        if(cur == nullptr)
            return false;

        if(depth == s.size())
        {
            if(cur->IsEnd == 0)
                return false;

            cur->IsEnd--;

            if(cur->IsEnd == 0 && IsEmpty(cur))
            {
                delete cur;
                return true;
            }

            return false;
        }

        int idx = s[depth] - 'a';

        if(Delete(cur->child[idx], s, depth + 1))
        {
            cur->child[idx] = nullptr;
        }

        else
        {
            if(cur->child[idx] == nullptr)
                return false;

            level[cur->child[idx]->depth].erase(
                level[cur->child[idx]->depth].find(
                    cur->child[idx]->Prefix
                )
            );

            cur->child[idx]->Prefix--;

            level[cur->child[idx]->depth].insert(
                cur->child[idx]->Prefix
            );
        }

        if(cur != root &&
           cur->IsEnd == 0 &&
           IsEmpty(cur))
        {
            delete cur;
            return true;
        }

        return false;
    }

    void erase(string &s)
    {
        if(!SearchWord(s))
            return;

        Delete(root, s);
    }

    int MaxPrefixAtDepth(int d)
    {
        if(level[d].empty())
            return 0;

        return *level[d].rbegin();
    }
};
