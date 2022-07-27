#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    int K; cin >> K;
    vector<int> dp(N,numeric_limits<int>::max());
    vector<int> h(N);
    dp[0] = 0;
    for(int i = 0; i < N; i++) cin >> h[i];

    for(int i = 0; i < N; i++) {
        for(int j = 1; j <= K; j++) {
            if(i+j < N) {
                dp[i+j] = min(dp[i+j],dp[i] + abs(h[i]-h[i+j]));
            }
        }
    }

    cout << dp[N-1] << endl;
}