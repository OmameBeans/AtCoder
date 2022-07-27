#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<vector<int>> dp(N+1,vector<int>(3)), cost(N,vector<int>(3));

    for(int i = 0; i < N; i++) 
        for(int j = 0; j < 3; j++) cin >> cost[i][j];

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < 3; j++) {
            for(int nj = 0; nj < 3; nj++) {
                if(j == nj) {
                    if(i+2 <= N) {
                        dp[i+2][nj] = max(dp[i+2][nj],dp[i][j]+cost[i][j]);
                    }
                } else {
                    if(i+1 <= N) {
                        dp[i+1][nj] = max(dp[i+1][nj],dp[i][j]+cost[i][j]);
                    }
                }
            }
        }
    }

    int ans = 0;

    for(int i = 0; i < 3; i++) {
        ans = max(ans,dp[N][i]);
    }

    cout << ans << endl;
}