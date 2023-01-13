#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int T; cin >> T;
    while(T--) {
        int N; cin >> N;
        int cnt = 0;
        for(int i = 0; i < N; i++) {
            int x; cin >> x;
            if(x%2 != 0) cnt++;
        }
        cout << cnt << endl;
    }
}