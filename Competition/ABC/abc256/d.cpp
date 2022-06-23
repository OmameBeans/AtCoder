#include<bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> imos(200010);
    for(int i = 0; i < N; i++) {
        int l,r; cin >> l >> r;
        imos[l]++;
        imos[r]--;
    }

    for(int i = 0; i < 200009; i++) imos[i+1] += imos[i];

    int L = -1, R = -1;

    for(int i = 0; i < 200010; i++) {
        if(imos[i] > 0 && L == -1) L = i;
        if(imos[i] <= 0 && L != -1) {
            cout << L << " " << i << endl;
            L = -1;
        }
    }
}