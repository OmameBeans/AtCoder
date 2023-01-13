#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int T; cin >> T;
    while(T--) {
        ll N; cin >> N;
        ll p,q;
        for(ll i = 2; i*i*i <= N; i++) {
            if(N%i == 0) {
                if((N/i)%i==0) {
                    p = i;
                    q = N/i/i;
                } else {
                    p = (ll)round(sqrt(N/i));
                    q = i;
                }
                break;
            }
        }
        cout << p << " " << q << endl;
    }
}