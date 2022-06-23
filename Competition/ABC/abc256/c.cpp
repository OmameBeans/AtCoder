#include<bits/stdc++.h>
using namespace std;

int main() {
    vector<int> h(3),w(3);
    for(int i = 0; i < 3; i++) cin >> h[i];
    for(int i = 0; i < 3; i++) cin >> w[i];

    long long ans = 0;

    for(int a = 1; a <= 30; a++) {
        for(int b = 1; b <= 30; b++) {
            for(int c = 1; c <= 30; c++) {
                for(int d = 1; d <= 30; d++) {
                    if(h[0]-(a+b) <= 0 || h[1]-(c+d) <= 0 || w[0]-(a+c) <= 0 || w[1]-(b+d) <= 0) continue;
                    int X = w[2] - h[1] - h[0] + a+b+c+d;
                    int Y = h[2] - w[1] - w[0] + a+b+c+d;
                    // cout << a << " " << b << " " << c << " " << d << endl;
                    // cout << X << " " << Y << endl;
                    if(X > 0 && Y > 0 && X == Y) ans++;
                }
            }
        }
    }

    cout << ans << endl;
}