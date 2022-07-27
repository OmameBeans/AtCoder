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

mint dp1[100010], dp2[100010];
bool seen[100010];

void dfs(
    int i,
    vector<vector<int>> &G
) {
    dp1[i] = dp2[i] = 1;
    seen[i] = true;
    bool sink = true;
    for(int ni : G[i]) {
        if(!seen[ni]) {
            sink = false;
            dfs(ni,G);
            dp1[i] *= dp1[ni] + dp2[ni];
            dp2[i] *= dp1[ni];
        }
    }

    if(sink) {
        return;
    }
}

int main() {
    int N; cin >> N;
    vector<vector<int>> G(N);
    for(int _ = 0; _ < N-1; _++) {
        int x,y; cin >> x >> y;
        x--,y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i = 0; i < N; i++) seen[i] = false;

    dfs(0,G);

    cout << dp1[0] + dp2[0] << endl;
}