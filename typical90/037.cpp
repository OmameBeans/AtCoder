#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for (int i = 0; i < (n); ++i)
#define DREP(i,s,n) for(int i = (s); i < (n); i++)
template<class T> inline bool chmin(T& a, T b) {if (a > b) {a = b;return true;}return false;}
template<class T> inline bool chmax(T& a, T b) {if (a < b) {a = b;return true;}return false;}
using ll = long long;
using P = pair<int,int>;
using Pl = pair<long long,long long>;
using veci = vector<int>;
using vecl = vector<long long>;
using vecveci = vector<vector<int>>;
using vecvecl = vector<vector<long long>>;
const int MOD = 1000000007;
const double pi = acos(-1);
ll gcd(ll a, ll b) {if(b == 0) return a; else return gcd(b,a%b);}
ll lcm(ll a, ll b) {return a*b/gcd(a,b);}

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
    void init(int siz) {val.assign(siz*4,e);}
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

const int MAX = 10010;

int main() {
    int W,N; cin >> W >> N;
    auto f = [](ll a, ll b) -> ll{return max(a,b);};
    ll e = -(1LL<<60);
    SegTree<ll> dp(MAX,f,e), pre_dp(MAX,f,e);
    dp.set(0,0LL);
    vector<int> L(N),R(N);
    vector<ll> V(N);
    REP(i,N) cin >> L[i] >> R[i] >> V[i];
    for(int i = 1; i <= N; i++) {
        swap(dp.val,pre_dp.val);
        dp.init(MAX);
        for(int j = 0; j < W+1; j++) {
            dp.update(j,pre_dp.query(j,j+1),f);
            dp.update(j,pre_dp.query(j-R[i-1],j-L[i-1]+1)+V[i-1],f);
        }
    }
    if(dp.query(W,W+1) > 0) cout << dp.query(W,W+1) << endl;
    else cout << -1 << endl;
    return 0;
}