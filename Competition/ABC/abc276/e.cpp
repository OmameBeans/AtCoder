#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for (int i = 0; i < (n); ++i)
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

struct UnionFind {
    vector<int> par,siz,edge;
    UnionFind(int sz) : par(sz),siz(sz,1),edge(sz) {
        for(int i = 0; i < sz; i++) par[i] = i;
    }
    int root(int x) {
        while(par[x] != x) {
            x = par[x];
        }
        return x;
    }
    bool merge(int x, int y) {
        x = root(x);
        y = root(y);
        if(x == y) {
            edge[x]++;
            return false;
        }
        if(siz[x] < siz[y]) swap(x,y);
        siz[x] += siz[y];
        edge[x] += edge[y]+1;
        par[y] = x;
        return true;
    }
    bool same(int x, int y) {return root(x) == root(y);}
    int size(int x) {return siz[root(x)];}
    int cal_edge(int x) {return edge[root(x)];}
};

int main() {
    int H,W; cin >> H >> W;
    map<P,int> idx;
    map<int,P> ori;
    vector<string> C(H);
    int si,sj;
    REP(i,H) cin >> C[i];
    int cnt = 0;
    REP(i,H) REP(j,W) {
        idx[{i,j}] = cnt;
        ori[cnt] = {i,j};
        cnt++;
        if(C[i][j] == 'S') {
            si = i, sj = j;
        }
    }
    int di[] = {-1,0,1,0};
    int dj[] = {0,-1,0,1};

    UnionFind UT(H*W);

    REP(i,H) REP(j,W) {
        REP(dir,4) {
            int ni = i+di[dir];
            int nj = j+dj[dir];
            if(ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
            if(C[i][j] != '.' || C[ni][nj] != '.') continue;
            UT.merge(idx[{i,j}],idx[{ni,nj}]);
        }
    }

    REP(dir1,4) {
        REP(dir2,dir1) {
            int i1 = si+di[dir1];
            int j1 = sj+dj[dir1];
            int i2 = si+di[dir2];
            int j2 = sj+dj[dir2];
            if(i1 < 0 || i1 >= H || j1 < 0 || j1 >= W) continue;
            if(i2 < 0 || i2 >= H || j2 < 0 || j2 >= W) continue;
            if(UT.same(idx[{i1,j1}],idx[{i2,j2}])) {
                cout << i1 << " " << j1 << " " << i2 << " " << j2 << endl;
                cout << "Yes" << endl;
                return 0;
            }
        }
    }
    cout << "No" << endl;
    return 0;
}