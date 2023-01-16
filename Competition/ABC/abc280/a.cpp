#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int H,W; cin >> H >> W;
    vector<string> S(H);
    for(int i = 0; i < H; i++) cin >> S[i];
    int cnt = 0;
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(S[i][j] == '#') cnt++;
        }
    }
    cout << cnt << endl;
}