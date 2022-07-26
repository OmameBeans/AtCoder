//verify : https://atcoder.jp/contests/practice2/tasks/practice2_f

#include <bits/stdc++.h>
using namespace std;

class NTT {
    private : 
        static const int e = 23;
        const long long mod = 998244353; // mod = u * 2^e + 1
        const int u = 119;
        long long g = 3;
        long long w[e+1], invw[e+1];
    public :
        long long modpow(long long a, long long n) {
            if(n == 0) return 1;
            auto t = modpow(a,n/2);
            t = t*t;
            t %= mod;
            if(n & 1) {
                t = t*a;
                t %= mod;
            }
            return t;
        }

        void init() {
            w[e] = modpow(g,u);
            invw[e] = modpow(modpow(g,mod-2),u);

            for(int i = e; i > 0; i--) {
                w[i-1] = w[i]*w[i];
                w[i-1] %= mod;
                invw[i-1] = invw[i]*invw[i];
                invw[i-1] %= mod;
            }
        }

        void DFT(vector<long long> &f, bool inverse = false) {
            int n = f.size();
            int logn = log2(n);
            if(n == 1) return;

            vector<long long> f0(n/2),f1(n/2);

            for(int i = 0; i < n/2; i++) {
                f0[i] = f[2*i];
                f1[i] = f[2*i+1];
            }

            DFT(f0,inverse);
            DFT(f1,inverse);

            long long a = 1, k;

            if(inverse) {
                k = invw[logn];
            } else {
                k = w[logn];
            }

            for(int i = 0; i < n; i++) {
                int n2 = n/2;
                f[i] = f0[i%n2] + (a * f1[i%n2])% mod;
                f[i] %= mod;
                a *= k;
                a %= mod;
            }
        }

        template<typename T>
        vector<long long> Convolute(vector<T> &g, vector<T> &h) {
            int n = (1<<e); 

            vector<long long> ng(n), nh(n);

            for(int i = 0; i < n; i++) {
                if(i < g.size()) ng[i] = g[i];
                if(i < h.size()) nh[i] = h[i];
            }

            DFT(ng);
            DFT(nh);

            for(int i = 0; i < n; i++) {
                ng[i] *= nh[i];
                ng[i] %= mod;
            }

            DFT(ng,true);

            auto invn = modpow(n,mod-2);

            for(int i = 0; i < n; i++) {
                ng[i] *= invn;
                ng[i] %= mod;
            }

            return ng;
        }
};

int main() {
    int N,M; cin >> N >> M;
    vector<long long> A(N),B(M);

    for(int i = 0; i < N; i++) cin >> A[i];
    for(int i = 0; i < M; i++) cin >> B[i];

    NTT ntt;
    ntt.init();
    auto f = ntt.Convolute<long long>(A,B);

    for(int i = 0; i < N+M-1; i++) cout << f[i] << " ";
    cout << endl;
}