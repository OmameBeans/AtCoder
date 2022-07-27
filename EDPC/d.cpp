#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int N,W; cin >> N >> W;
    vector<int> w(N), v(N);
    vector<vector<ll>> dp(N+1,vector<ll>(100010));
    
    for(int i = 0; i < N; i++) cin >> w[i] >> v[i];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 100010; j++) {
            dp[i+1][j] = max(dp[i+1][j],dp[i][j]);
            if(j+w[i] < 100010) {
                dp[i+1][j+w[i]] = max(dp[i+1][j+w[i]], dp[i][j] + v[i]);
            }
        }
    }

    cout << dp[N][W] << endl;
}