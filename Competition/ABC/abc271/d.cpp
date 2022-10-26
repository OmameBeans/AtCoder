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
    int N,S; cin >> N >> S;
    veci a(N),b(N);
    REP(i,N) cin >> a[i] >> b[i];
    vecveci dp(110,veci(10010));
    vecveci pre(110,veci(10010,-1));

    dp[0][0] = 1;

    REP(i,N) REP(j,10010) {
        if(dp[i][j] == 0) continue;
        if(j+a[i] < 10010) {
            dp[i+1][j+a[i]] |= dp[i][j];
            pre[i+1][j+a[i]] = 0;
        }
        if(j+b[i] < 10010) {
            dp[i+1][j+b[i]] |= dp[i][j];
            pre[i+1][j+b[i]] = 1;
        }
    }

    // REP(i,N+1) {
    //     REP(j, S+1) {
    //         cout << pre[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    string ans = "";

    if(!dp[N][S]) {
        cout << "No" << endl;
        return 0;
    }

    cout << "Yes" << endl;

    for(int i = N-1; i >= 0; i--) {
        if(pre[i+1][S] == 0) {
            ans += 'H';
            S -= a[i];
        } else {
            ans += 'T';
            S -= b[i];
        }
    }

    reverse(ans.begin(),ans.end());
    cout << ans << endl;

    return 0;
}