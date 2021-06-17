#include<bits/stdc++.h>
using namespace std;
using ll = long long;

void bfs(vector<vector<int>> &G, int N, int s, vector<int> &dist) {
    dist.assign(N,-1);
    dist[s] = 0;
    queue<int> que;
    que.push(s);
    while(que.size()) {
        int v = que.front();
        que.pop();
        for(int nv : G[v]) {
            if(dist[nv] != -1) continue;
            dist[nv] = dist[v] + 1;
            que.push(nv);
        }
    }
}