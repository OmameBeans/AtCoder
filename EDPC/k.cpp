#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    int K; cin >> K;
    vector<int> a(N); 
    for(int i = 0; i < N; i++) cin >> a[i];
    vector<bool> dp(K+1,false);
    
    for(int i = 1; i <= K; i++) {
        bool ok = false;
        for(int j = 0; j < N; j++) {
            if(i-a[j] < 0) dp[i] = false;
            else {
                if(dp[i-a[j]] == false) ok = true;
            }
        }
        dp[i] = ok;
    }

    if(dp[K]) cout << "First" << endl;
    else cout << "Second" << endl;
}