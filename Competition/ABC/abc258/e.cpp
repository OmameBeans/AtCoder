#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for (int i = 0; i < (n); ++i)
template<class T> inline bool chmin(T& a, T b) {if (a > b) {a = b;return true;}return false;}
template<class T> inline bool chmax(T& a, T b) {if (a < b) {a = b;return true;}return false;}
using ll = long long;
using P = pair<int,int>;
using Pl = pair<long long,long long>;
using veci = vector<int>;
using vecl = vector<long long>;
using vecveci = vector<vector<int>>;
using vecvecl = vector<vector<long long>>;
const int MOD = 1000000007;
const double pi = acos(-1);
ll gcd(ll a, ll b) {if(b == 0) return a; else return gcd(b,a%b);}
ll lcm(ll a, ll b) {return a*b/gcd(a,b);}

template<int MOD> struct Fp {
    long long val;
    constexpr Fp(long long v = 0) noexcept : val(v % MOD) {if (val < 0) val += MOD;}
    constexpr int getmod() { return MOD; }
    constexpr Fp operator - () const noexcept {return val ? MOD - val : 0;}
    constexpr Fp operator + (const Fp& r) const noexcept { return Fp(*this) += r; }
    constexpr Fp operator - (const Fp& r) const noexcept { return Fp(*this) -= r; }
    constexpr Fp operator * (const Fp& r) const noexcept { return Fp(*this) *= r; }
    constexpr Fp operator / (const Fp& r) const noexcept { return Fp(*this) /= r; }
    constexpr Fp& operator += (const Fp& r) noexcept {val += r.val;if (val >= MOD) val -= MOD;return *this;}
    constexpr Fp& operator -= (const Fp& r) noexcept {val -= r.val;if (val < 0) val += MOD;return *this;}
    constexpr Fp& operator *= (const Fp& r) noexcept {val = val * r.val % MOD;return *this;}
    constexpr Fp& operator /= (const Fp& r) noexcept {long long a = r.val, b = MOD, u = 1, v = 0;while (b) {long long t = a / b;a -= t * b; swap(a, b);u -= t * v; swap(u, v);}val = val * u % MOD;if (val < 0) val += MOD;return *this;}
    constexpr bool operator == (const Fp& r) const noexcept {return this->val == r.val;}
    constexpr bool operator != (const Fp& r) const noexcept {return this->val != r.val;}
    friend constexpr ostream& operator << (ostream &os, const Fp<MOD>& x) noexcept {return os << x.val;}
    friend constexpr Fp<MOD> modpow(const Fp<MOD> &a, long long n) noexcept {if (n == 0) return 1;auto t = modpow(a, n / 2);t = t * t;if (n & 1) t = t * a;return t;}
};

using mint = Fp<MOD>;

int main() {
    int N,Q; cin >> N >> Q;
    ll X; cin >> X;
    ll tot_W = 0;
    vecl W(N); REP(i,N) {
        cin >> W[i];
        tot_W += W[i];
    }
    vecl K(Q);
    REP(i,Q) cin >> K[i];
    veci ep(N);
    vecl cnt_from_sp(N);

    vecvecl dp(60,vecl(N,0)), next(60,vecl(N,-1));
    REP(i,N) {
        dp[0][i] = W[i];
        next[0][i] = (i+1)%N;
    }

    for(int i = 1; i < 30; i++) {
        for(int j = 0; j < N; j++) {
            next[i][j] = next[i-1][next[i-1][j]];
            dp[i][j] = dp[i-1][j] + dp[i-1][next[i-1][j]];
        }
    }

    REP(sp,N) {
        ll l = -1, r = N;
        ll nX = X;
        nX %= tot_W;
        while(r-l > 1) {
            ll mid = (r-l)/2 + l; // spからmid個の合計を計算する
            ll tot = 0;
            int cur = sp;
            for(int i = 0; i < 30; i++) {
                if(mid & (1LL<<i)) {
                    tot += dp[i][cur];
                    cur = next[i][cur];
                }
            }
            if(tot >= nX) r = mid;
            else l = mid;
        }

        cnt_from_sp[sp] = (X/tot_W) * N + r;
    }

    // REP(i,N) cout << cnt_from_sp[i] << " ";
    // cout << endl;

    vecvecl next_sp(60,vecl(N));

    REP(i,N) {
        next_sp[0][i] = (i + cnt_from_sp[i]) % N;
    }

    for(int i = 1; i < 60; i++) {
        for(int j = 0; j < N; j++) {
            next_sp[i][j] = next_sp[i-1][next_sp[i-1][j]];
        }
    }

    // REP(s,5) {
    //     REP(j,N) cout << next_sp[s][j] << " ";
    //     cout << endl;
    // }

    REP(i,Q) {
        K[i]--;
        int cur = 0;
        REP(s,60) {
            if(K[i] & (1LL<<s)) {
                //cout << K[i] << " " << s << endl;
                cur = next_sp[s][cur];
            }
        }

        //cout << cur << endl;

        cout << cnt_from_sp[cur] << endl;
    }

    return 0;
}