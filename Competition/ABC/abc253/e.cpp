#include <bits/stdc++.h>
#define REP(i,n) for (int i = 0; i < (n); ++i)
template<class T> inline bool chmin(T& a, T b) {if (a > b) {a = b;return true;}return false;}
template<class T> inline bool chmax(T& a, T b) {if (a < b) {a = b;return true;}return false;}
using namespace std;
using ll = long long;
using P = pair<int,int>;
using Pl = pair<long long,long long>;
using veci = vector<int>;
using vecl = vector<long long>;
using vecveci = vector<vector<int>>;
using vecvecl = vector<vector<long long>>;
const int MOD = 998244353;
const double pi = acos(-1);
ll gcd(ll a, ll b) {if(b == 0) return a; else return gcd(b,a%b);}
ll lcm(ll a, ll b) {return a*b/gcd(a,b);}

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

template<typename T>
struct SegTree {
    using Fx = function<T(T,T)>; //セグメント木に載せる関数
    int n;//葉の数
    const T e; //単位元
    Fx f;
    vector<T> val; //二分木の配列
    SegTree(int siz, Fx F, T E) : n(),f(F),e(E),val(siz*4,e) {
        int x = 1;
        while(siz > x) x *= 2;
        n = x;
    }
    //位置iの要素をxにする
    void set(int i, T x) {
        i += n-1;
        val[i] = x;
        while(i > 0) {
            i = (i-1)/2;
            val[i] = f(val[2*i+1],val[2*i+2]);
        }
    }
    //位置iの要素をF(val[i],x)に置き換える
    void update(int i, T x, Fx F) {
        i += n-1;
        val[i] = F(val[i],x);
        while(i>0) i=(i-1)/2,val[i] = f(val[i*2+1],val[i*2+2]);
    }
    //[a,b)の要素にfを適用する
    T query(int a, int b) {return query_sub(a,b,0,0,n);}
    T query_sub(int a,int b,int k,int l,int r) {
        if(r <= a || b <= l) return e;
        else if(a <= l && r <= b) return val[k];
        else {
            T v1 = query_sub(a,b,2*k+1,l,(l+r)/2);
            T v2 = query_sub(a,b,2*k+2,(l+r)/2,r);
            return f(v1,v2);
        }
    }
};

int main() {
    int N,M,K; cin >> N >> M >> K;
    auto f = [](mint a, mint b) -> mint{return a+b;};
    mint e = 0;

    SegTree<mint> dp(5050,f,e);

    for(int i = 1; i <= M; i++) {
        dp.set(i,1);
        //cout << i << " " << dp.query(i,i+1) << endl;
    }

    for(int i = 1; i < N; i++) {
        auto pre = dp;

        for(int a = 0; a < 5050; a++) dp.set(i,0);

        for(int a = 1; a <= M; a++) {
            mint k = 0;
            if(K > 0) k += pre.query(1,a-K+1) + pre.query(a+K,M+1);
            else k += pre.query(1,M+1);

            dp.set(a,k);

            //cout << a << " " << k << endl;
        }
    }

    mint ans = 0;
    for(int i = 1; i <= M; i++) {
        ans += dp.query(i,i+1);
    }

    cout << ans << endl;
}