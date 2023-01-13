#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N; cin >> N;
    vector<string> S(N);
    for(int i = 0; i < N; i++) cin >> S[i];
    for(int i = N-1; i >= 0; i--) cout << S[i] << endl;
}