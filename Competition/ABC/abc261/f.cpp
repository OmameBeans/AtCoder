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
    int C; cin >> C;
    veci T(N),A(N);
    REP(i,N) cin >> T[i] >> A[i];

    vector<vecveci> op(2,vecveci(N+1,veci(30)));
    REP(k,30) op[1][0][k] = 1;
    vecveci dp(30,veci(N+1));

    REP(i,2) {
        REP(j,N) {
            REP(k,30) {
                if(T[j] == 1) {
                    op[i][j+1][k] = (op[i][j][k] & (1 & (A[j]>>k)));
                } else if(T[j] == 2) {
                    op[i][j+1][k] = (op[i][j][k] | (1 & (A[j]>>k)));
                } else {
                    op[i][j+1][k] = (op[i][j][k] ^ (1 & (A[j]>>k)));
                }
                //cout << op[i][j][k] << endl;
            }
        }
    }

    // REP(j,2) {
    //     cout << j << endl;
    //     REP(k,30) {
    //         REP(i,N+1) cout << op[j][i][k] << " ";
    //         cout << endl;
    //     }
    // }

    REP(k,30) {
        dp[k][0] = (1 & (C>>k));
    }

    REP(i,30) REP(j,N) {
        //out << op[dp[i][j]][j+1][i] << endl;
        dp[i][j+1] = op[dp[i][j]][j+1][i];
    }

    // REP(i,30) {
    //     REP(j,N+1) cout << dp[i][j] << " ";
    //     cout << endl;
    // }

    for(int i = 1; i <= N; i++) {
        int tot = 0;
        REP(k,30) {
            if(dp[k][i]) tot += 1<<k;
        }
        cout << tot << endl;
    }

    return 0;
}