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

const double INF = numeric_limits<double>::max();

double dist(vector<double> &x, vector<double> &y, int i, int j) {
    return sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
}

int main() {
    int N; cin >> N;
    int M; cin >> M;
    vector<double> x,y;
    x.push_back(0);
    y.push_back(0);
    REP(i,N) {
        double a,b; cin >> a >> b;
        x.push_back(a);
        y.push_back(b);
    }
    REP(i,M) {
        double a,b; cin >> a >> b;
        x.push_back(a);
        y.push_back(b);
    }
    vector<vector<double>> dp((1<<(N+M+1)),vector<double>(N+M+1,INF));
    dp[0][0] = 0;
    for(int S = 0; S < (1<<(N+M+1)); S++) {
        int T = 0;
        for(int t = N+1; t < N+M+1; t++) {
            if(S & (1<<t)) T++;
        }
        for(int v = 0; v < N+M+1; v++) {
            for(int nv = 0; nv < N+M+1; nv++) {
                if(S != 0 && !(S & (1<<v))) continue;
                if(S & (1<<nv)) continue;
                int nS = S | (1<<nv);
                if(v != nv) {
                    dp[nS][nv] = min(dp[nS][nv],dp[S][v]+dist(x,y,v,nv)/(double)(1<<T));
                }
            }
        }
    }

    double ans = INF;

    for(int S = 0; S < 1<<(N+M+1); S++) {
        bool ok = true;
        for(int v = 1; v < N+1; v++) {
            if(!(S & (1<<v))) ok = false;
        }
        if(ok) {
            ans = min(ans,dp[S][0]);
            //cout << dp[S][0] << endl;
        }
    }

    printf("%.10f\n",ans);

    return 0;
}