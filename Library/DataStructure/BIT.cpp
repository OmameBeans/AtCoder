#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
struct BIT{
    int N;
    vector<T> bit;
    BIT(int n) : N(n+1), bit(N,0) {}
    void add(int i, T x) {
        for(int idx = i; idx < N; idx += (idx & -idx)) bit[idx] += x;
    }
    T sum(int i) {
        T tot(0);
        for(int idx = i; idx > 0; idx -= (idx & -idx)) tot += bit[idx];
        return tot;
    }
    T sum(int l, int r) {return sum(r) - sum(l);}
    int lower_bound(T w) {
        if(w <= 0) return 0;
        else {
            int x = 0, r = 1;
            while(r < N) r = r << 1;
            for(int len = r; len > 0; len /= 2) {
                if(x+len < N && bit[x+len] < w) {
                    w -= bit[x+len];
                    x += len;
                }
            }
            return x+1;
        }
    }
};

const int MAX = 100010;

ll Number_of_inversions(vector<int> A) {
    int M = A.size();
    ll tot = 0;
    BIT<int> seg(MAX);
    for(int i = 0; i < M; i++) {
        tot += seg.sum(A[i]+1,MAX);
        seg.add(A[i],1);
    }
}