#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int N,M; cin >> N >> M;
    vector<vector<int>> G(N);
    for(int i = 0; i < M; i++) {
        int u,v; cin >> u >> v;
        u--,v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> seen(N);
    auto dfs = [&](auto dfs, int i) -> void{
        seen[i] = 1;
        for(int ni : G[i]) {
            if(seen[ni]) continue;
            dfs(dfs,ni);
        }
    };

    int cnt = 0;

    for(int i = 0; i < N; i++) {
        if(!seen[i]) cnt++;
        dfs(dfs,i);
    }

    cout << cnt << endl;
}