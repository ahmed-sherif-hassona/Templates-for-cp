struct Trie{
    struct Node{
        Node* child[26];
        int IsEnd, Prefix;

        Node(){
            memset(child, 0, sizeof child);
            IsEnd = Prefix = 0;
        }
    };

    Node* root = new Node();

    void insert(string &s)
    {
        Node* cur = root;

        for(auto it : s)
        {
            int idx = it - 'a';

            if(cur->child[idx] == 0)
                cur->child[idx] = new Node();

            cur = cur->child[idx];
            cur->Prefix++;
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

            cur->child[idx]->Prefix--;
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

        Node* cur = root;

        for(auto c : s)
        {
            int idx = c - 'a';
            cur = cur->child[idx];
            cur->Prefix--;
        }

        Delete(root, s);
    }
};
