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

int main() {
    int N,M; cin >> N >> M;
    vector<string> S(N), T(M);
    map<string,int> mp;
    REP(i,N) cin >> S[i];
    REP(i,M) {
        cin >> T[i];
        mp[T[i]]++;
    }

    sort(S.begin(),S.end());

    set<string> st;

    auto dfs = [&](auto dfs, int now, int rest, vector<string> L) -> void {
        if(now == N-1) {
            string ans = "";
            REP(i,N) ans += L[i];
            //cout << ans << endl;
            if(ans.size() >= 3) st.insert(ans);
            return;
        }

        REP(i,rest+1) {
            string pre = L[now];
            REP(j,i) L[now] += '_';
            dfs(dfs,now+1,rest-i,L);
            L[now] = pre;
        }
    };
    
    do
    {
        auto nS = S;
        int rest = 16;
        REP(i,N) {
            if(i < N-1) nS[i] += '_';
            rest -= nS[i].size();
        }
        int now = 0;
        dfs(dfs, now ,rest,nS);
    } while (next_permutation(S.begin(),S.end()));

    for(auto s : st) {
        if(!mp[s]) {
            cout << s << endl;
            return 0;
        }
    }    

    cout << -1 << endl;

    return 0;
}