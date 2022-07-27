#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void dfs(
    int l,
    int r,
    vector<ll> &a,
    vector<vector<ll>> &dp
) {
    if(dp[l][r] != -1) return;
    if(l == r) {
        dp[l][r] = a[l];
        return;
    }

    dfs(l+1,r,a,dp);
    dfs(l,r-1,a,dp);

    dp[l][r] = max(a[l]-dp[l+1][r],a[r]-dp[l][r-1]);
}

int main() {
    int N; cin >> N;
    vector<ll> a(N);
    for(int i = 0; i < N; i++) cin >> a[i];

    vector<vector<ll>> dp(N,vector<ll>(N,-1));

    dfs(0,N-1,a,dp);

    cout << dp[0][N-1] << endl;
}