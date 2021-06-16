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

int LIS(vector<int> &A, int N,vector<int> &dp) {
    const int INF = 1<<30;
    dp = vector<int>(N+1,INF);
    for(int i = 0; i < N; i++) {
        auto itr = upper_bound(dp.begin(),dp.end(),A[i])-dp.begin();
        dp[itr] = A[i];
    }
    for(int i = N-1; i >= 0; i--) {
        if(dp[i] != INF) {
            return i+1;
        }
    }
    return 0;
}

int main() {
    int N; cin >> N;
    vector<int> A(N); for(int i = 0; i < N; i++) cin >> A[i];
    vector<int> dp;
    cout << LIS(A,N,dp) << endl;
    return 0;
}