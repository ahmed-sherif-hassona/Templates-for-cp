struct KMP {
    vector<int> pi;
    vector<int> ans;
    void calcPrefix(string&p) {
        int m=p.size();
        pi.assign(m,0);
        for (int i=1,j=0;i<m;i++) {
            while (j>0&&p[i]!=p[j])
                j=pi[j-1];

            if (p[i]==p[j])
                j++;

            pi[i]=j;
        }
    }
    void kmp(string&s,string&p) {
        ans.clear();
        calcPrefix(p);
        for (int i=0,j=0;i<(int)s.size();i++) {
            while (j>0&&s[i]!=p[j])
                j=pi[j-1];

            if (s[i]==p[j])
                j++;
          
            if (j==(int)p.size()) {
                ans.push_back(i-(int)p.size()+1);
                j=pi[j-1];
            }
        }
    }
};
