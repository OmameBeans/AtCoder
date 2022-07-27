#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = numeric_limits<ll>::max();

int main() {
    int N,W; cin >> N >> W;
    vector<int> w(N), v(N);
    vector<vector<ll>> dp(N+1,vector<ll>(100010,INF));

    dp[0][0] = 0;
    
    for(int i = 0; i < N; i++) cin >> w[i] >> v[i];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 100010; j++) {
            if(dp[i][j] == INF) continue;
            dp[i+1][j] = min(dp[i+1][j],dp[i][j]);
            if(j+v[i] < 100010) {
                dp[i+1][j+v[i]] = min(dp[i+1][j+v[i]], dp[i][j] + w[i]);
            }
        }
    }

    int ans;

    for(int i = 0; i < 100010; i++) {
        if(dp[N][i] <= W) ans = i;
    }

    cout << ans << endl;
}