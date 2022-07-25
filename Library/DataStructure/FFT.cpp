//verify : https://atcoder.jp/contests/atc001/tasks/fft_c

#include <bits/stdc++.h>
using namespace std;
double pi = acos(-1);

class FFT {
    public : 
        static void DFT(vector<complex<double>> &f, bool inverse = false) {
            int n = f.size();
            if(n == 1) return;

            vector<complex<double>> f0,f1;

            for(int i = 0; i < n; i++) {
                if(i%2 == 0) f0.push_back(f[i]);
                else f1.push_back(f[i]);
            }

            DFT(f0,inverse);
            DFT(f1,inverse);

            complex<double> a = 1, r;

            if(inverse) {
                r = polar(1.0,-2.0*pi/n);
            } else {
                r = polar(1.0,2.0*pi/n);
            }

            for(int i = 0; i < n; i++) {
                int n2 = n/2;
                f[i] = f0[i%n2] + a * f1[i%n2];
                a *= r;
            }
        }

        template<typename T>
        static vector<double> Convolute(vector<T> &g, vector<T> &h) {
            int n = 1; //畳み込み配列のサイズ
            while(g.size() + h.size() > n) n *= 2;

            vector<complex<double>> ng(n), nh(n);

            for(int i = 0; i < n; i++) {
                if(i < g.size()) ng[i] = g[i];
                if(i < h.size()) nh[i] = h[i];
            }

            DFT(ng);
            DFT(nh);

            vector<complex<double>> gh(n);

            for(int i = 0; i < n; i++) gh[i] = ng[i]*nh[i];

            DFT(gh,true);

            vector<double> ans(n);

            for(int i = 0; i < n; i++) ans[i] = gh[i].real()/n;

            return ans;
        }
};

int main() {
    int N; cin >> N;
    vector<double> A(N+1),B(N+1);

    for(int i = 1; i <= N; i++) cin >> A[i] >> B[i];

    FFT fft;

    auto f = fft.Convolute<double>(A,B);

    for(int i = 1; i <= 2*N; i++) cout << (int)round(f[i]) << endl;
}