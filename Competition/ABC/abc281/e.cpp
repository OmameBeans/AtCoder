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
const int MOD = 998244353;
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
    int N,M,K; cin >> N >> M >> K;
    vecl A(N); REP(i,N) cin >> A[i];
    multiset<ll> X,Y;
    ll tot = 0;
    REP(i,M) {
        if(X.size() < K) {
            X.insert(A[i]);
            tot += A[i];
        } else {
            if(*(--X.end()) <= A[i]) {
                Y.insert(A[i]);
            } else {
                tot -= *(--X.end());
                tot += A[i];
                Y.insert(*(--X.end()));
                X.erase(X.find(*(--X.end())));
                X.insert(A[i]);
            }
        }
    }

    cout << tot << " ";

    for(int i = 0; i < N-M; i++) {
        ll a = A[i];
        ll b = A[i+M];

        if(X.count(a)) {
            tot -= a;
            X.erase(X.find(a));
            if(Y.size() > 0) {
                X.insert(*Y.begin());
                tot += *Y.begin();
                Y.erase(Y.find(*Y.begin()));
            } 
        } else {
            Y.erase(Y.find(a));
        }

        if(X.size() < K) {
            X.insert(b);
            tot += b;
        } else {
            if(*(--X.end()) <= b) {
                Y.insert(b);
            } else {
                tot -= *(--X.end());
                tot += b;
                Y.insert(*(--X.end()));
                X.erase(X.find(*(--X.end())));
                X.insert(b);
            }
        }

        cout << tot << " ";
    }
    cout << endl;
}