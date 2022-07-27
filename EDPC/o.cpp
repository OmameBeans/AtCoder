#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = (int)(1e9)+7;

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

mint dp[22][1<<21];

int main() {
    int N; cin >> N;
    vector<vector<int>> a(N,vector<int>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cin >> a[i][j];
        }
    }

    dp[0][0] = 1;

    for(int i = 0; i < N; i++) {
        for(int S = 0; S < (1<<N); S++) {
            if(dp[i][S] == 0) continue; // <-- 枝刈り
            for(int j = 0; j < N; j++) {
                if(1<<j & S) continue;
                int nS = S | (1<<j);
                if(a[i][j]) dp[i+1][nS] += dp[i][S];
            }
        }
    }

    cout << dp[N][(1<<N)-1] << endl;
}

