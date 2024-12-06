#include<bits/stdc++.h>
using namespace std;

#define int long long
#define pii pair<int, int>
#define all(a) a.begin(), a.end()
// Time Complexity: O(nlogn)

void count_sort(vector<int> &p,vector<int> &c){  // Sorts values in p by keys in c i.e, if c[p[i]] < c[p[j]] then i appears before j in p.
    int n = p.size();
    vector<int> cnt(n);
    for(auto x : c) cnt[x]++;
    vector<int> p_new(n),pos(n);
    pos[0] = 0;
    for(int i=1;i<n;++i) pos[i] = pos[i-1] + cnt[i-1];
    for(auto x : p){
        int i = c[x];
        p_new[pos[i]] = x;
        pos[i]++;
    }
    p = p_new;
}

// Returns sorted suffix_array of size (n+1) with first element = n (empty suffix).
pair<vector<int>, vector<int>> suffix_array(string s){
    s += '$';
    int n = s.size();
    vector<int> p(n),c(n); // p stores suffix array and c stroes its equivalence class
    {
        // k = 0 phase
        vector<pair<char,int>> a(n);
        for(int i=0;i<n;++i) a[i] = {s[i],i};
        sort(all(a));
        for(int i=0;i<n;++i) p[i] = a[i].second;
        c[p[0]] = 0;
        for(int i=1;i<n;++i){
            if(a[i].first == a[i-1].first) c[p[i]] = c[p[i-1]];
            else c[p[i]] = c[p[i-1]] + 1;
        }
    }
    int k=0;
    while((1<<k) < n ){ // k -> k + 1
        // We require to sort p by {c[i], c[i+(1<<k)]} value. So we use radix sort: Sort the second element of pair then count sort first element in a stable fashion.
        // Sort by second element: p[i] -= (1<<k). As p[i]'s are already sorted by c[i] values.
        for(int i = 0; i < n ; ++i) p[i] = (p[i] - (1<<k) + n )%n;
        count_sort(p,c);
        
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        for(int i=1;i<n;++i){
            pii prev = {c[p[i-1]] , c[(p[i-1] + (1<<k))%n] } ;
            pii now = {c[p[i]] , c[(p[i] + (1<<k))%n] } ;
            if( now == prev) c_new[p[i]] = c_new[p[i-1]];
            else c_new[p[i]] = c_new[p[i-1]] + 1;
        }
        c = c_new;
        ++k;
    }
    return {p, c}; 
}


vector<int> lcp_array(vector<int> &p,vector<int> &c,string s){
    int n = p.size();
    vector<int> lcp(n-1);
    int k=0;
    for(int i=0;i<n-1;++i){
        int pi = c[i];
        int j = p[pi-1];
        //lcp[i] = lcp[s[i...],s[j...]]
        while(s[i+k] == s[j+k]) ++k;
        lcp[pi-1] = k;  
        k = max(k-1,0ll);
    }
    return lcp;
}
// firstinds lcp using p and 
// c array defined in suffix array

struct SegmentTree {
    vector<int> tree;
    int n;

    void build(vector<int> &arr) {
        n = arr.size();
        tree.assign(4 * n + 1, 1e9);
        build(1, 0, n - 1, arr);
    }

    void build(int v, int tl, int tr, vector<int> &arr) {
        if(tl == tr) {
            tree[v] = arr[tl];
        }else {
            int tm = (tl + tr) / 2;
            build(2 * v, tl, tm, arr);
            build(2 * v + 1, tm + 1, tr, arr);
            tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        }
    }

    int query(int v, int tl, int tr, int l, int r) {
        // cout << v << endl;
        if(tl > r || tr < l) {
            return 1e9;
        }else if(tl >= l && tr <= r) {
            return tree[v];
        }else {
            int tm = (tl + tr) / 2;
            int ql = query(2 * v , tl, tm, l, r);
            int qr = query(2 * v + 1, tm + 1, tr, l, r);
            return min(ql, qr);
        }
    }
    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    } 
    void disp() {
        for(int i = 1; i <= 4 * n; i++) {
            if(tree[i] == 1e9) cout << ". ";
            else cout << tree[i] << ' ';
        }
        cout << endl;
    }
};

void solve()
{  
    string s;
     cin >> s;

    s.push_back('#');
    int n = s.size();
    int m; cin >> m;
    
    vector<int> ind;
    for(int i = 0; i < m; i++) {
        ind.push_back(s.size());
        string t; cin >> t;
        for(auto c: t) s.push_back(c);
    }
    ind.push_back(s.size());

    auto [p, c] = suffix_array(s);
    auto lcp = lcp_array(p, c, s);
    auto ip = p;
    for(int i = 0; i < p.size(); i++) {
        ip[p[i]] = i;
    }

    // cout << s << endl;
    // for(auto x: p) {
    //     cout << x << ' ';
    // }
    // cout << endl;
    // for(auto x: ip) {
    //     cout << x << ' ';
    // }
    // cout << endl;

    vector<int> prev(s.size() + 2, -1), next(s.size() + 2, -1);
    for(int i = 1; i <= s.size(); i++) {
        if(p[i] < n) prev[i] = i;
        else prev[i] = prev[i - 1];
    }
    for(int i = s.size(); i >= 0; i--) {
        if(p[i] < n) next[i] = i;
        else next[i] = next[i + 1];
    }
    // for(auto x: prev) {
    //     cout << x << ' ';
    // }
    // cout << endl;
    // for(auto x: next) {
    //     cout << x << ' ';
    // }
    // cout << endl;

    SegmentTree st;
    st.build(lcp);
    // st.disp();

    auto LCP = [&](int l, int r) {
        return st.query(l, r-1);
    };
    // cout << LCP(12, 13) << endl;
    // cout << st.query(12, 12) << endl;

    for(int i = 0; i < m; i++) {
        int cnt = 0;
        int j = ind[i];
        // cout << n << ' ' << j << ' ' << ip[j] << ' ' << prev[ip[j]] << ' ' << next[ip[j]] << endl;
        while(j < ind[i + 1]) {
            int t = 0;
            if(prev[ip[j]] != -1) {
                int q = LCP(prev[ip[j]], ip[j]);
                // cout << q << endl;
                t = max(t, q);
            }
            if(next[ip[j]] != -1) {
                // cout << "Tt" << next[ip[j]] << endl;
                int q = LCP(ip[j], next[ip[j]]);
                t = max(t, q);
            }
            // cout << "T: " << t << endl;
            if(!t) {
                cnt = -1;
                break;
            }else {
                cnt++;
                j += t;
            }
        }
        cout << cnt << '\n';
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t=1;
    // cin>>t;

    while(t--){
        solve();
    }

    return 0;
}