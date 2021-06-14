#include<bits/stdc++.h>
using ll = long long;

ll B = 1007, MOD = 1000000007;

//SにTが含まれていれば，trueを，そうでなければ，elseを返す．
bool StringSearch(string S, string T) {
    int N = S.size();
    int M = T.size();
    if(N < M) return 0;
    ll t = 1;
    for(int i = 0; i < M; i++) t *= B, t %= MOD;
    ll Hash_T = 0,Hash_S = 0;
    for(int i = 0; i < M; i++) {
        Hash_S = Hash_S*B + (ll)S[i], Hash_S %= MOD;
        Hash_T = Hash_T*B + (ll)T[i], Hash_T %= MOD;
    }
    if(Hash_S == Hash_T) return 1;
    for(int i = 1; i < N; i++) {
        if(i+M-1 >= N) continue;
        Hash_S = Hash_S*B, Hash_S %= M;
        Hash_S -= ((ll)S[i-1]*T)%M;
        Hash_S = (Hash_S+M)%M;
        Hash_S += (ll)S[i+M-1];
        Hash_S %= M;
        if(Hash_S == Hash_T) return 1;
    }
    return 0;
}

