#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll INF = 1LL<<60;
int N;
vector<ll> a(410), a_S(410);
vector<vector<bool>> seen(410,vector<bool>(410));
vector<vector<ll>> dp(410,vector<ll>(410,INF));

void dfs(int l, int r) {
    if(seen[l][r]) return;
    seen[l][r] = true;
    if(l+1 == r) {
        dp[l][r] = 0;
        return;
    }
    for(int k = l+1; k < r; k++) {
        dfs(l,k);
        dfs(k,r);
        dp[l][r] = min(dp[l][r],dp[l][k]+dp[k][r]+a_S[r]-a_S[l]);
    }
}

int main() {
    cin >> N;
    for(int i = 0; i < N; i++) cin >> a[i], a_S[i+1] = a_S[i]+a[i];
    dfs(0,N);
    cout << dp[0][N] << endl;
}