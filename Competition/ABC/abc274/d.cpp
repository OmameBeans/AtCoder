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
    int N; cin >> N;
    int x,y; cin >> x >> y;
    veci A(N); REP(i,N) cin >> A[i];
    veci eA,oA;
    REP(i,N) if(i%2 == 0) eA.push_back(A[i]); else oA.push_back(A[i]);
    vecveci dp1(1010,veci(20010)), dp2(1010,veci(20010));
    int BASE = 10010;

    dp1[0][BASE] = dp2[0][BASE] = 1;
    REP(i,eA.size()) {
        REP(j,20010) {
            if(i == 0) {
                if(j+eA[i] < 20010) dp1[i+1][j+eA[i]] |= dp1[i][j];
            } else {
                if(j+eA[i] < 20010) dp1[i+1][j+eA[i]] |= dp1[i][j];
                if(j-eA[i] >= 0) dp1[i+1][j-eA[i]] |= dp1[i][j];
            }
        }
    }

    REP(i,oA.size()) {
        REP(j,20010) {
            if(j+oA[i] < 20010) dp2[i+1][j+oA[i]] |= dp2[i][j];
            if(j-oA[i] >= 0) dp2[i+1][j-oA[i]] |= dp2[i][j];
        }
    }

    // REP(j,20010) {
    //     if(dp1[eA.size()][j]) cout << j-BASE << endl;
    // }

    if(dp1[eA.size()][x+BASE] && dp2[oA.size()][y+BASE]) cout << "Yes" << endl;
    else cout << "No" << endl;
    return 0;
}