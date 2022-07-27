#include <bits/stdc++.h>
using namespace std;

void dfs(
    vector<vector<int>> &G,
    int i,
    vector<int> &dp
) {
    if(dp[i] != -1) return;
    if(G[i].size() == 0) {
        dp[i] = 0;
        return;
    }
    for(int ni : G[i]) {
        dfs(G,ni,dp);
        dp[i] = max(dp[i],dp[ni]+1);
    }
}

int main() {
    int N,M; cin >> N >> M;
    vector<vector<int>> G(N);
    for(int _ = 0; _ < M; _++) {
        int a,b; cin >> a >> b;
        a--,b--;
        G[a].push_back(b);
    }
    vector<int> dp(N,-1);

    for(int i = 0; i < N; i++) {
        dfs(G,i,dp);
    }

    int ans = 0;

    for(int i = 0; i < N; i++) {
        ans = max(ans,dp[i]);
    }

    cout << ans << endl;
}