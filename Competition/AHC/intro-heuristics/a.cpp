#include<bits/stdc++.h>
#include <chrono>
#include <random>
using namespace std;
using ll = long long;

random_device seed;
mt19937 mt(seed());

struct intoro_heuristics{
    int D;
    vector<ll> c, last;
    vector<vector<ll>> s;
    vector<ll> t;
    vector<set<int>> last_d;
    ll T0, T1;
    double TL, T;

    intoro_heuristics(int _D, ll _T0, ll _T1) : D(_D), T0(_T0), T1(_T1) {
        c.assign(26,0);
        t.assign(D+1,0);
        last.assign(26,0);
        last_d.assign(26,set<int>());
        s.assign(D+1,vector<ll>(26));
        for(int type = 0; type < 26; type++) {
            last_d[type].insert(0);
            last_d[type].insert(D+1);
        }
        TL = 1980;
    }

    void input() {
        for(int i = 0; i < 26; i++) cin >> c[i];
        for(int i = 1; i <= D; i++) for(int j = 0; j < 26; j++) cin >> s[i][j];
        // for(int i = 1; i <= D; i++) {
        //     cin >> t[i];
        //     t[i]--;
        // }
    }

    void output() {
        for(int d = 1; d <= D; d++) printf("%lld\n",t[d]+1LL);
    }

    //t[i]が与えられている場合
    void give_init(ll &tot) {
        for(int type = 0; type < 26; type++) last[type] = 0;
        tot = 0;
        for(int d = 1; d <= D; d++) {
            tot += s[d][t[d]];
            last[t[d]] = d;
            last_d[t[d]].insert(d);
            for(int type = 0; type < 26; type++) tot -= c[type] * (d - last[type]);
        }
    }

    inline void greedy(ll &tot) {
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
        tot = ans;
    }

    ll naive_change(int d, int q) {
        for(int type = 0; type < 26; type++) last[type] = 0;
        auto nt = t;
        nt[d] = q;
        ll tot = 0;
        for(int d = 1; d <= D; d++) {
            tot += s[d][nt[d]];
            last[t[d]] = d;
            for(int type = 0; type < 26; type++) tot -= c[type] * (d - last[type]);
        }
        return tot;
    }

    inline void add_d(int d, int q, ll &tot) {
        int l = *prev(last_d[q].lower_bound(d));
        int r = *last_d[q].upper_bound(d);
        last_d[q].insert(d);
    
        //cout << l << " " << r << endl;
    
        tot += c[q]*(d-l)*(r-d);
    }
 
    inline void erase_d(int d, int q, ll &tot) {
        int l = *prev(last_d[q].lower_bound(d));
        int r = *last_d[q].upper_bound(d);
        last_d[q].erase(d);
    
        //cout << l << " " << r << endl;
    
        tot -= c[q]*(d-l)*(r-d);
    }
 
    inline void fast_change(int d, int q, ll &tot) {
        int old_q = t[d];
        tot -= s[d][old_q];
        tot += s[d][q];

        int l = 0, r = D+1;
        for(int i = d-1; i >= 1; i--) if(t[i] == q) {
            l = i;
            break;
        }
        for(int i = d+1; i <= D; i++) if(t[i] == q) {
            r = i;
            break;
        }
        tot += c[q]*(d-l)*(r-d);

        l = 0, r = D+1;
        for(int i = d-1; i >= 1; i--) if(t[i] == old_q) {
            l = i;
            break;
        }
        for(int i = d+1; i <= D; i++) if(t[i] == old_q) {
            r = i;
            break;
        }
        tot -= c[old_q]*(d-l)*(r-d);
        
        t[d] = q;
    }

    inline void random_change(ll &init_ans) {
        uniform_int_distribution<int> day(1,D), type(0,25);
        uniform_real_distribution<double> rand(0,100);

        auto old = init_ans;

        int d = day(mt), q = type(mt);

        int old_q = t[d];

        fast_change(d,q,old);

        ll delta = old - init_ans;

        if(prob(delta,T) >= (double)rand(mt)/100.0) {
            init_ans = old;
        } else {
            t[d] = old_q;
        }
    }

    inline void swap_random(ll &init_ans) {
        uniform_int_distribution<int> day(1,D);
        uniform_real_distribution<double> rand(0,100);

        int d1 = day(mt), d2 = min(d1+16,day(mt));

        auto old = init_ans;

        int q1 = t[d1], q2 = t[d2];

        fast_change(d1,q2,old);
        fast_change(d2,q1,old);

        ll delta = old - init_ans;

        if(prob(delta,T) >= rand(mt)/100.0) {
            init_ans = old;
        } else {
            swap(t[d1],t[d2]);
        }
    }

    inline double prob(ll delta, double T) {
        if(delta >= 0) return 1;
        else return exp(delta/T);
    }

    inline void simulated_annealing(ll &tot) {
        uniform_int_distribution<int> dist(0,100);

        auto t1 = std::chrono::high_resolution_clock::now();
        auto t2 = std::chrono::high_resolution_clock::now();

        ll cnt = 0;
        double T; //温度

        while(1) {
            //温度の更新
            t2 = std::chrono::high_resolution_clock::now();
            double t =  std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            if(t >= TL) break;
            if(cnt % 80 == 0) {
                t /= TL;
                if(t >= 1.0) break;
                else {
                    T = pow(T0,1-t) * pow(T1,t);
                }
            }

            cnt++;

            if(dist(mt) <= 60) {
                random_change(tot);
            } else {
                swap_random(tot);
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int D; cin >> D;
    intoro_heuristics solver(D,(ll)(2e3),(ll)(6e2));
    solver.input();
    ll tot = 0;
    solver.greedy(tot);

    // auto t1 = std::chrono::high_resolution_clock::now();
    // auto t2 = std::chrono::high_resolution_clock::now();
    // while(std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() <= 1980) {
    //     int t = dist(mt);
    //     if(t == 0) solver.random_change(tot);
    //     else solver.swap_random(tot);
    //     t2 = std::chrono::high_resolution_clock::now();
    // }

    solver.simulated_annealing(tot);

    solver.output();
}
