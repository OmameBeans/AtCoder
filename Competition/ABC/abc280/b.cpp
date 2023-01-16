#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N; cin >> N;
    vector<ll> S(N);
    for(int i = 0; i < N; i++) cin >> S[i];
    vector<ll> A(N);
    ll tot = 0;
    for(int i = 0; i < N; i++) {
        A[i] = S[i] - tot;
        tot += A[i];
    }
    for(int i = 0; i < N; i++) cout << A[i] << " ";
    cout << endl;
}