#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct edge{
    int to;
    ll cost;
};

void dijkstra(vector<vector<edge>> &G, int V, int s, vector<ll> &dist) {
    dist.assign(V,1LL<<60);
    dist[s] = 0;
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> que;
    que.push({0,s});
    while(que.size()) {
        auto p = que.top();
        que.pop();
        int n = p.second;
        ll d = p.first;
        if(dist[n] < d) continue;
        for(auto e : G[n]) {
            if(dist[e.to] > dist[n] + e.cost) {
                dist[e.to] = dist[n] + e.cost;
                que.push({dist[e.to],e.to});
            }
        }
    }
}