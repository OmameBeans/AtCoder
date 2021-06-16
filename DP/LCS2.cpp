#include <bits/stdc++.h>
using namespace std;

int LCS(string S, string T) {
    int N = S.size();
    int M = T.size();
    vector<int> pre_dp;
    vector<int> dp(M+1);
    for(int i = 0; i < N; i++) {
        pre_dp = dp;
        dp = vector<int>(M+1);
        for(int j = 0; j < M; j++) {
            if(S[i] == T[j]) dp[j+1] = pre_dp[j] + 1;
            else dp[j+1] = max(dp[j],pre_dp[j+1]);
        }
    }
    return dp[M];
}
int main() {
    int t; cin >> t;
    while(t--) {
        string S,T; cin >> S >> T;
        cout << LCS(S,T) << endl;
    }
    return 0;
}