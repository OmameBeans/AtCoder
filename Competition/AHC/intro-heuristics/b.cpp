#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct intoro_heuristics{
    int D;
    vector<ll> c, last;
    vector<vector<ll>> s;
    vector<ll> t;
    vector<set<int>> last_d;

    intoro_heuristics(int _D) : D(_D) {
        c.assign(26,0);
        t.assign(D+1,0);
        last.assign(26,0);
        last_d.assign(26,set<int>());
        s.assign(D+1,vector<ll>(26));
    }

    void input() {
        for(int i = 0; i < 26; i++) cin >> c[i];
        for(int i = 1; i <= D; i++) for(int j = 0; j < 26; j++) cin >> s[i][j];
        for(int i = 1; i <= D; i++) {
            cin >> t[i];
            t[i]--;
            last_d[t[i]].insert(0);
            last_d[t[i]].insert(D);
        }
    }

    void output() {
        for(int d = 1; d <= D; d++) cout << t[d]+1 << endl;
    }

    //t[i]が与えられている場合
    void give_init(ll &tot) {
        tot = 0;
        for(int d = 1; d <= D; d++) {
            tot += s[d][t[d]];
            last[t[d]] = d;
            for(int type = 0; type < 26; type++) tot -= c[type] * (d - last[type]);
            cout << tot << endl;
        }
    }

    void naive_change(int d, int q) {
        for(int type = 0; type < 26; type++) last[type] = 0;
        t[d] = q;
        ll tot = 0;
        for(int d = 1; d <= D; d++) {
            tot += s[d][t[d]];
            last[t[d]] = d;
            for(int type = 0; type < 26; type++) tot -= c[type] * (d - last[type]);
        }
        cout << tot << endl;
    }

    void add_d(int d, int q, ll &tot) {
        int d_pre = *last_d[q].lower_bound(d);
        int d_next = *last_d[q].upper_bound(d);

        tot += c[q] * (d_next-d_pre) * (d_next-d_pre-1) / 2;
        tot -= c[q] * (d_next-d) * (d_next-d-1) / 2;
        tot -= c[q] * (d-d_pre) * (d-d_pre) / 2;

        last_d[q].insert(d);
    }

    void erase_d(int d, int q, ll &tot) {
        int d_pre = *last_d[q].lower_bound(d);
        int d_next = *last_d[q].upper_bound(d);

        tot -= c[q] * (d_next-d_pre) * (d_next-d_pre-1) / 2;
        tot += c[q] * (d_next-d) * (d_next-d-1) / 2;
        tot += c[q] * (d-d_pre) * (d-d_pre) / 2;

        last_d[q].erase(d);
    }

    void fast_change(int d, int q, ll &tot) {
        int old_q = t[d];
        tot -= s[d][old_q];
        tot += s[d][q];
        add_d(d,q,tot);
        erase_d(d,q,tot);
    }

    void greedy() {
        ll ans = 0;
        for(int d = 1; d <= D; d++) {
            int type_d = -1;
            ll cost_d = 0;
            ll neg_cost = 0;
            for(int type = 0; type < 26; type++) {
                neg_cost += c[type]*(d-last[type]);
            }
            for(int type = 0; type < 26; type++) {
                if(cost_d < s[d][type] + c[type]*(d-last[type])) {
                    cost_d = s[d][type] + c[type]*(d-last[type]);
                    type_d = type;
                }
            }
            ans += cost_d - neg_cost;
            last[type_d] = d;
            last_d[type_d].insert(d);
            t[d] = type_d;
        }
    }
};

int main() {
    int D; cin >> D;
    intoro_heuristics solver(D);
    solver.input();
    int M; cin >> M;
    ll tot = 0;
    solver.give_init(tot);
    for(int _ = 0; _ < M; _++) {
        int d,q; cin >> d >> q;
        q--;
        solver.fast_change(d,q,tot);
        cout << tot << endl;
    }
}