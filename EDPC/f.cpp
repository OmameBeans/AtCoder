#include <bits/stdc++.h>
using namespace std;

int main() {
    string s,t; cin >> s >> t;
    int N = s.size(), M = t.size();

    vector<vector<int>> dp(N+1,vector<int>(M+1));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(s[i] == t[j]) {
                dp[i+1][j+1] = dp[i][j] + 1;
            } else {
                dp[i+1][j+1] = max(dp[i+1][j],dp[i][j+1]);
            }
        }
    }

    string ans = "";

    while(N > 0 && M > 0) {
        if(dp[N][M] == dp[N-1][M]) N--;
        else if(dp[N][M] == dp[N][M-1]) M--;
        else {
            N--,M--;
            ans += s[N];
        }
    }

    reverse(ans.begin(),ans.end());

    cout << ans << endl;
}