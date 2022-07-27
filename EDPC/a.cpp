#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> dp(N,numeric_limits<int>::max());
    vector<int> h(N);
    dp[0] = 0;
    for(int i = 0; i < N; i++) cin >> h[i];

    for(int i = 0; i < N; i++) {
        if(i+1 < N) {
            dp[i+1] = min(dp[i+1],dp[i] + abs(h[i]-h[i+1]));
        }
        if(i+2 < N) {
            dp[i+2] = min(dp[i+2],dp[i] + abs(h[i]-h[i+2]));
        }
    }

    cout << dp[N-1] << endl;
}