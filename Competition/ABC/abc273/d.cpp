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
    int H,W; cin >> H >> W;
    int rs,cs; cin >> rs >> cs;
    rs--,cs--;
    map<int,set<int>> t,y;
    t[cs].insert(-1);
    t[cs].insert(H);
    y[rs].insert(-1);
    y[rs].insert(W);
    int N; cin >> N;
    REP(i,N) {
        int r,c; cin >> r >> c;
        r--,c--;
        t[c].insert(-1);
        t[c].insert(H);
        t[c].insert(r);
        y[r].insert(-1);
        y[r].insert(W);
        y[r].insert(c);
    }
    int Q; cin >> Q;
    while(Q--) {
        char d;
        int l;
        cin >> d >> l;
        if(d == 'L') {
            if(y[rs].empty()) {
                cs -= l;
                cs = max(0,cs);
            } else {
                auto lb = *prev(y[rs].lower_bound(cs));
                l = min(l,cs-(lb+1));
                cs -= l;
            }
        } else if(d == 'R') {
            if(y[rs].empty()) {
                cs += l;
                cs = min(cs,W-1);
            } else {
                auto rb = *y[rs].lower_bound(cs);
                l = min(l,(rb-1)-cs);
                cs += l;
            }
        } else if(d == 'U') {
            if(t[cs].empty()) {
                rs -= l;
                rs = max(rs,0);
            } else {
                auto ub = *prev(t[cs].lower_bound(rs));
                l = min(l,rs-(ub+1));
                rs -= l;
            }
        } else {
            if(t[cs].empty()) {
                rs += l;
                rs = min(rs,H-1);
            } else {
                auto db = *t[cs].lower_bound(rs);
                l = min(l,(db-1)-rs);
                rs += l;
            }
        }
        cout << rs+1 << " " << cs+1 << endl;
    }
    return 0;
}