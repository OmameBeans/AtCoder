#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1000000007;

struct nCrmod{
    vector<ll> fac,finv,inv;
    int MAX;
    nCrmod(int siz) : MAX(siz), fac(siz), finv(siz) , inv(siz) {
        fac[0] = fac[1] = 1;
        finv[0] = finv[1] = 1;
        inv[1] = 1;
        for (int i = 2; i < siz; i++){
            fac[i] = fac[i - 1] * i % MOD;
            inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
            finv[i] = finv[i - 1] * inv[i] % MOD;
        }
    }
    // n,kがそこまで大きくない
    ll com1(int n, int k) {
        if (n < k) return 0;
        if (n < 0 || k < 0) return 0;
        return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
    }
    //nがでかい
    ll com2(ll n, ll k) {
        if (n < k) return 0;
        if (n < 0 || k < 0) return 0;
        ll p = 1,q = 1;
        for(int i = 0; i < k; i++) {
            p *= n-i, p %= MOD;
            q *= inv[i+1], q %= MOD;
        }
        return (p * q) % MOD;
    }

    ll COM(ll n, ll k) {
        if(n >= MAX) return com2(n,k);
        else return com1(n,k);
    }
};