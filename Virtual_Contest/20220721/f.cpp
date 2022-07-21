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

int di[] = {-1,0,1,0};
int dj[] = {0,-1,0,1};

int main() {
    int H,W,N,M; cin >> H >> W >> N >> M;
    vector<vecveci> dist(H,vecveci(W,veci(4,-1)));
    vecveci block(H,veci(W));
    vecveci reach(H,veci(W));
    queue<tuple<int,int,int>> que;
    REP(i,N) {
        int a,b; cin >> a >> b;
        a--,b--;
        REP(dir,4) {
            que.push({a,b,dir});
            dist[a][b][dir] = 0;
        }
    }
    REP(i,M) {
        int a,b; cin >> a >> b;
        a--,b--;
        block[a][b] = 1;
    }
    while(que.size()) {
        auto p = que.front();
        que.pop();
        int i = get<0>(p);
        int j = get<1>(p);
        int dir = get<2>(p);
        REP(k,4) {
            if(k != dir) continue;
            int ni = i+di[k];
            int nj = j+dj[k];
            if(ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
            if(block[ni][nj]) continue;
            if(dist[ni][nj][dir] == -1) {
                dist[ni][nj][dir] = dist[i][j][dir] + 1;
                que.push({ni,nj,dir});
            }
        }
    }
    int ans = 0;

    REP(i,H) REP(j,W) {
        REP(dir,4) {
            if(dist[i][j][dir] != -1) {
                reach[i][j] = 1;
                break;
            }
        }
    }

    // REP(i,H) {
    //     REP(j,W) cout << reach[i][j] << " ";
    //     cout << endl;
    // }

    REP(i,H) REP(j,W) if(reach[i][j]) ans++;

    cout << ans << endl;
    return 0;
}