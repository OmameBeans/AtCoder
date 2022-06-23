#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int V; //頂点数
    vector<vector<int>> G,rG; // G : グラフ，rG : 辺を逆向きにしたグラフ
    vector<bool> seen; //訪問済みかどうか
    vector<int> cmp,vs,sz; //cmp:属する番号 vs:帰りがけ順 sz:連結成分数
 
    SCC(int _V) : V(_V) {
        G = rG = vector<vector<int>>(V);
        seen.assign(V,false);
        cmp.assign(V,0);
        sz.assign(V,0);
    }
 
    void add_edge(int u, int v) {
        G[u].push_back(v);
        rG[v].push_back(u);
    }
 
    void dfs(int v) {
        seen[v] = true;
        for(int nv : G[v]) {
            if(seen[nv]) continue;
            dfs(nv);
        }
        vs.push_back(v);
    }
 
    void rdfs(int v, int k) {
        seen[v] = true;
        cmp[v] = k;
        sz[k]++;
        for(int nv : rG[v]) {
            if(seen[nv]) continue;
            rdfs(nv,k);
        }
    }
 
    int scc() {
        seen.assign(V,false);
        for(int v = 0; v < V; v++) {
            if(seen[v]) continue;
            dfs(v);
        }
        seen.assign(V,false);
        int k = 0;
        for(int i = vs.size()-1; i >= 0; i--) {
            int v = vs[i];
            if(seen[v]) continue;
            rdfs(v,k);
            k++;
        }
        return k;
    }
 
    bool same(int a, int b) {
        return (cmp[a] == cmp[b]);
    }

    int group(int v) {
        return cmp[v];
    }
 
    int size(int v) {
        return sz[cmp[v]];
    }
};

int main() {
    int N; cin >> N;
    SCC S(N);
    vector<long long> X(N), min_cost(N,1LL<<60);
    for(int i = 0; i < N; i++) {
        int X; cin >> X;
        X--;
        S.add_edge(i,X);
    }
    for(int i = 0; i < N; i++) {
        cin >> X[i];
    }

    long long ans = 0;

    S.scc();

    for(int v = 0; v < N; v++) {
        if(S.size(v) < 2) continue;
        min_cost[S.group(v)] = min(min_cost[S.group(v)], X[v]);
    }

    for(int i = 0; i < N; i++) {
        if(min_cost[i] != 1LL<<60) ans += min_cost[i];
    }

    cout << ans << endl;
}