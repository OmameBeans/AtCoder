#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll f(ll q, ll ex) {
    ll l = 0, r = 1e12+10;
    while(r-l > 1) {
        ll mid = (r-l)/2 + l;
        ll cnt = 0;
        ll nq = q;
        for(int _ = 0; _ < (log(mid)/log(q)); _++) {
            cnt += mid/nq;
            nq *= q;
        }
        if(ex <= cnt) r = mid;
        else l = mid;
    }
    return r;
}

ll pow(ll a, ll n) {
    ll ans = 1;
    for(int i = 0; i < n; i++) ans *= a;
    return ans;
}

int main() {
    ll K; cin >> K;
    ll ans = 0;
    for(ll i = 2; i*i <= K; i++) {
        if(K%i == 0) {
            int ex = 0;
            while(K%i == 0) {
                ex++;
                K /= i;
            }
            ans = max(ans,f(i,ex));
        }
    }
    if(K != 1) ans = max(ans,f(K,1));
    cout << ans << endl;
}