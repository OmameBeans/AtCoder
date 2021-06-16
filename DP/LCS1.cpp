#include <bits/stdc++.h>
using namespace std;

int LCS(string S, string T, string &ans) {
    int N = S.size();
    int M = T.size();
    vector<vector<int>> dp(N+1,vector<int>(M+1));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(S[i] == T[j]) dp[i+1][j+1] = dp[i][j] + 1;
            else dp[i+1][j+1] = max(dp[i+1][j],dp[i][j+1]);
        }
    }
    ans = "";
    while(N > 0 && M > 0) {
        if(dp[N][M] == dp[N-1][M]) N--;
        else if(dp[N][M] == dp[N][M-1]) M--;
        else {
            N--,M--,ans += S[N];
        }
    }
    reverse(ans.begin(),ans.end());
    return dp[N][M];
}

int main() {
    string S,T; cin >> S >> T;
    string ans;
    LCS(S,T,ans);
    cout << ans << endl;
    return 0;
}