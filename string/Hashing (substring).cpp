#include<bits/stdc++.h>
using namespace std;

struct StringHashing {
private:
    using ll = long long;

    const ll mod1 = 1e9 + 7;
    const ll mod2 = 1e9 + 9;

    ll base1, base2;
    int n;

    vector<ll> pw1, pw2;
    vector<pair<ll,ll>> pre, suf;

    void build_powers(int sz) {
        pw1.assign(sz + 1, 1);
        pw2.assign(sz + 1, 1);

        for (int i = 1; i <= sz; i++) {
            pw1[i] = (pw1[i - 1] * base1) % mod1;
            pw2[i] = (pw2[i - 1] * base2) % mod2;
        }
    }

    void build_prefix(string &s, vector<pair<ll,ll>> &arr) {
        ll a = 0, b = 0;

        for (int i = 0; i < n; i++) {
            a = (a * base1 + s[i]) % mod1;
            b = (b * base2 + s[i]) % mod2;

            arr[i] = {a, b};
        }
    }

public:

    StringHashing(string s, ll b1 = 127, ll b2 = 131) {
        base1 = b1;
        base2 = b2;

        n = s.size();

        pw1.resize(n + 1);
        pw2.resize(n + 1);

        pre.resize(n);
        suf.resize(n);

        build_powers(n);

        build_prefix(s, pre);

        reverse(s.begin(), s.end());
        build_prefix(s, suf);

        reverse(s.begin(), s.end());
    }

    pair<ll,ll> getHash(vector<pair<ll,ll>> &arr, int l, int r) {
        auto res = arr[r];

        if (l > 0) {
            res.first =
                (res.first - arr[l - 1].first * pw1[r - l + 1]) % mod1;

            res.second =
                (res.second - arr[l - 1].second * pw2[r - l + 1]) % mod2;
        }

        if (res.first < 0) res.first += mod1;
        if (res.second < 0) res.second += mod2;

        return res;
    }

    bool isPalindrome(int l, int r) {
        return getHash(pre, l, r)
            == getHash(suf, n - r - 1, n - l - 1);
    }

    int count_unique_substrings() {
        int ans = 0;

        for (int len = 1; len <= n; len++) {

            set<pair<ll,ll>> st;

            for (int i = 0; i + len - 1 < n; i++) {
                st.insert(getHash(pre, i, i + len - 1));
            }

            ans += st.size();
        }

        return ans;
    }
};
