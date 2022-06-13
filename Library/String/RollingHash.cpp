#include <bits/stdc++.h>
using namespace std;

struct RollingHash {
    int N;
    long long B, MOD;
    vector<long long> Hash, inv;

    long long modpow(long long a, long long n, long long mod) {
        if(n == 0) return 1;
        long long t = modpow(a,n/2,mod);
        t = t*t;
        t %= mod;
        if(n & 1) {
            t *= a;
            t %= MOD;
        }
        return t;
    }
    
    RollingHash(string S, long long _B, long long _MOD) : N(S.size()), B(_B), MOD(_MOD) {
        Hash.assign(N+1,0LL);
        inv.assign(N+1,1LL);
        long long t = 1;
        long long f = modpow(B,MOD-2,MOD);
        for(int i = 0; i < N; i++) {
            Hash[i+1] = Hash[i] + (t * (long long)(S[i]))%MOD;
            Hash[i+1] %= MOD;
            inv[i+1] = inv[i]*f;
            inv[i+1] %= MOD;
            t *= B;
            t %= MOD;
        }
    }

    long long Substring(int pos, int sz) {
        long long ans = Hash[pos+sz] - Hash[pos];
        ans += MOD;
        ans %= MOD;
        ans *= inv[pos];
        ans %= MOD;
        return ans;
    }
};

int main() {
    string S,T; cin >> S >> T;
    long long MOD = 1000000007;
    long long B = 1007;
    RollingHash RHS(S,B,MOD);
    RollingHash RHT(T,B,MOD);

    int N = S.size();
    int M = T.size();

    for(int i = 0; i < N; i++) {
        if(i+M > N) continue;
        if(RHS.Substring(i,M) == RHT.Substring(0,M)) {
            cout << i << endl;
        }
    }
}