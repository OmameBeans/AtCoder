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
    string S,T; cin >> S >> T;
    int N = S.size();
    int M = T.size();

    vector<int> s(N),t(M), ts(N), tt(M);
    for(int i = 0; i < N; i++) s[i] = S[i]-'0', ts[i] = 1-s[i];
    for(int i = 0; i < M; i++) t[i] = T[i]-'0', tt[i] = 1-t[i];

    reverse(tt.begin(),tt.end());
    reverse(t.begin(),t.end());

    FFT fft;

    auto v1 = fft.Convolute<int>(s,tt);
    auto v2 = fft.Convolute<int>(ts,t);

    for(int i = 0; i < M; i++) cout << (int)(v1[M-1-i] + v2[M-1-i] + 0.5) << endl;
}