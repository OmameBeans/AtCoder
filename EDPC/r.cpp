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

int N;

vector<vector<mint>> multiply(
    vector<vector<mint>> &A, 
    vector<vector<mint>> &B
) {
    vector<vector<mint>> C(N,vector<mint>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

vector<vector<mint>> mat_init() {
    vector<vector<mint>> I(N,vector<mint>(N));
    for(int i = 0; i < N; i++) I[i][i] = 1;
    return I;
}

vector<vector<mint>> mat_pow(vector<vector<mint>> &A, ll K) {
    if(K == 0) return mat_init();
    auto t = mat_pow(A,K/2);
    t = multiply(t,t);
    if(K & 1) {
        t = multiply(t,A);
    }
    return t;
}

int main() {
    cin >> N;
    ll K; cin >> K;
    vector<vector<mint>> A(N,vector<mint>(N));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            int a; cin >> a;
            A[i][j] = a;
        }
    }

    A = mat_pow(A,K);

    mint ans = 0;

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) ans += A[i][j];
    }

    cout << ans << endl;
}

