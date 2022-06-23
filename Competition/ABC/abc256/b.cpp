#include<bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N;
    vector<int> A(N);
    for(int i = 0; i < N; i++) {
        cin >> A[i];
    }
    int P = 0;
    vector<int> B(4);
    for(int i = 0; i < N; i++) {
        B[0]++;
        vector<int> nB(4);
        for(int j = 0; j < 4; j++) {
            if(j + A[i] >= 4) P += B[j];
            else nB[j + A[i]] = B[j];
        }
        B = nB;
    }
    cout << P << endl;
}