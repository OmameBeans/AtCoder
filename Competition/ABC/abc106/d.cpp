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

long long modpow(long long a, long long n) {
    if(n == 0) return 1;
    auto t = modpow(a,n/2);
    t = t*t;
    t %= MOD;
    if(n & 1) {
        t = t*a;
        t %= MOD;
    }
    return t;
}

const int MAX = 310;

vector<ll> fac(MAX),finv(MAX),inv(MAX);

void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

ll COM(int n, int k) {
    if(n < k || (n < 0 || k < 0)) return 0;
    return fac[n]*(finv[k]*finv[n-k]%MOD)%MOD;
}

int main() {
    int N,K; cin >> N >> K;
    vecl A(N); REP(i,N) cin >> A[i];
    vecl Sum(K+1);
    for(int X = 0; X <= K; X++) {
        for(int i = 0; i < N; i++) {
            Sum[X] += modpow(A[i],X);
            Sum[X] %= MOD;
        }
    }
    COMinit();

    for(int X = 1; X <= K; X++) {
        ll tot = 0;
        for(int k = 0; k <= X; k++) {
            tot += (COM(X,k) * Sum[X-k]) % MOD * Sum[k] % MOD;
        }

        tot -= (modpow(2,X) * Sum[X]) % MOD;
        tot += MOD;
        tot %= MOD;

        tot *= modpow(2,MOD-2);
        tot %= MOD;

        cout << tot << endl;
    }
    return 0;
}