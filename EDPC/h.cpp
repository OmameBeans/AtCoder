#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = (int)(1e9)+7;

int main() {
    int H,W; cin >> H >> W;
    vector<string> a(H);
    for(int i = 0; i < H; i++) cin >> a[i];
    vector<vector<ll>> dp(H,vector<ll>(W));

    dp[0][0] = 1;

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(a[i][j] == '#') continue;
            if(i+1 < H && a[i+1][j] == '.') {
                dp[i+1][j] += dp[i][j];
                dp[i+1][j] %= MOD;
            }
            if(j+1 < W && a[i][j+1] == '.') {
                dp[i][j+1] += dp[i][j];
                dp[i][j+1] %= MOD;
            }
        }
    }

    cout << dp[H-1][W-1] << endl;
}