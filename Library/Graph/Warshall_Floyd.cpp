#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void Warshall_Floyd(vector<vector<ll>> &dist, int N) {
    for(int i = 0; i < N; i++) dist[i][i] = 0;
    for(int k = 0; k < N; k++) {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}