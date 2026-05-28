struct SuffixArray {
    string s;
    int n;
    vector<int> p, c, lcp, rankv;

    SuffixArray(string s) {
        this->s = s + '$';
        n = this->s.size();
        build_sa();
        build_lcp();
    }

    void build_sa() {
        p.resize(n);
        c.resize(n);

        // ---- k = 0 ----
        vector<pair<char,int>> a(n);
        for(int i = 0; i < n; i++)
            a[i] = {s[i], i};

        sort(a.begin(), a.end());

        for(int i = 0; i < n; i++)
            p[i] = a[i].second;

        c[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(a[i].first == a[i-1].first)
                c[p[i]] = c[p[i-1]];
            else
                c[p[i]] = c[p[i-1]] + 1;
        }

        // ---- k > 0 ----
        int k = 0;
        while((1 << k) < n) {
            for(int i = 0; i < n; i++) {
                p[i] = (p[i] - (1 << k) + n) % n;
            }

            counting_sort();

            vector<int> c_new(n);
            c_new[p[0]] = 0;

            int classes = 1;
            for(int i = 1; i < n; i++) {
                pair<int,int> cur = {c[p[i]], c[(p[i] + (1<<k)) % n]};
                pair<int,int> prev = {c[p[i-1]], c[(p[i-1] + (1<<k)) % n]};

                if(cur != prev) classes++;
                c_new[p[i]] = classes - 1;
            }

            c = c_new;
            k++;
        }
    }

    void counting_sort() {
        int n = p.size();
        int classes = *max_element(c.begin(), c.end()) + 1;

        vector<int> cnt(classes), pos(classes);

        for(int x : c)
            cnt[x]++;

        for(int i = 1; i < classes; i++)
            pos[i] = pos[i-1] + cnt[i-1];

        vector<int> p_new(n);

        for(int x : p) {
            int i = c[x];
            p_new[pos[i]++] = x;
        }

        p = p_new;
    }






    // compare pattern with suffix
    bool cmp(const string &pat, int pos) {
        int i = 0;
        while(i < (int)pat.size() && pos + i < n) {
            if(pat[i] != s[pos + i])
                return pat[i] < s[pos + i];
            i++;
        }
        return i == (int)pat.size();
    }

    bool exists(const string &pat) {
        int l = 0, r = n - 1;

        while(l <= r) {
            int mid = (l + r) / 2;

            int pos = p[mid];

            if(cmp(pat, pos))
                r = mid - 1;
            else
                l = mid + 1;
        }

        int idx = l;
        if(idx < n && idx > 0) {
            int pos = p[idx];
            if(!cmp(pat, pos)) return true;
        }

        // check neighbors (important!)
        for(int i = max(0, idx-1); i <= min(n-1, idx); i++) {
            int pos = p[i];
            bool ok = true;

            for(int j = 0; j < (int)pat.size(); j++) {
                if(pos + j >= n) { ok = false; break; }
                if(s[pos + j] != pat[j]) { ok = false; break; }
            }

            if(ok) return true;
        }

        return false;
    }





    void build_lcp() {
        rankv.resize(n);
        for(int i = 0; i < n; i++)
            rankv[p[i]] = i;

        lcp.assign(n, 0);

        int k = 0;
        for(int i = 0; i < n; i++) {
            if(rankv[i] == n - 1) {
                k = 0;
                continue;
            }

            int j = p[rankv[i] + 1];

            while(i + k < n && j + k < n &&
                  s[i + k] == s[j + k])
                k++;

            lcp[rankv[i]] = k;

            if(k) k--;
        }
    }
};


//////////////////////////////////////////////////////

int main() {
    string s;
    cin >> s;

    SuffixArray sa(s);

    // suffix array
    for(int i = 0; i < sa.p.size(); i++)
        cout << sa.p[i] << " ";
    cout << "\n";

    // lcp
    for(int i = 0; i < sa.lcp.size(); i++)
        cout << sa.lcp[i] << " ";
}
