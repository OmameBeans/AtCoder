struct edge{
    ll to;
    ll cost;
};
 
struct LCA {
    vector<vector<edge>> G;
    vector<vector<int>> parent;
    vector<vector<ll>> maxp, minp;
    vector<int> depth;
    vector<ll> dist;
    int V,s;
 
    LCA(vector<vector<edge>> _G, int _V) : G(_G), V(_V), s(log2(V+1)+1) {
        parent.assign(s,vector<int>(V,0));
        maxp.assign(s,vector<ll>(V,0));
        minp.assign(s,vector<ll>(V,1LL<<60));
        depth.assign(V,-1);
        dist.assign(V,0);
    }
 
    void init(int root = 0) {
        dfs(0,-1,0,0,0,1LL<<60);
        for(int i = 1; i < s; i++) {
            for(int j = 0; j < V; j++) {
                if(parent[i-1][j] >= 0) parent[i][j] = parent[i-1][parent[i-1][j]];
                else parent[i][j] = -1;
                maxp[i][j] = max(maxp[i-1][j],maxp[i-1][j+(1<<(i-1))]);
                minp[i][j] = min(minp[i-1][j],minp[i-1][j+(1<<(i-1))]);
            }
        }
    }
 
    void dfs(int i, int p, int d, ll c, ll ma, ll mi) {
        parent[0][i] = p;
        maxp[0][i] = ma;
        minp[0][i] = mi;
        dist[i] = c;
        depth[i] = d;
        for(auto e : G[i]) {
            if(e.to != p) {
                dfs(e.to,i,d+1,c+e.cost,max(ma,e.cost),min(mi,e.cost));
            }
        }
    }
 
    void print() {
        for(auto p : parent) {
            for(auto x : p) cout << x << " ";
            cout << endl;
        }
    }
 
    int query_LCA(int u, int v) {
        if(depth[u] < depth[v]) swap(u,v);
 
        int diff = abs(depth[u]-depth[v]);
        for(int i = 0; i < s; i++) {
            if(diff & (1<<i)) {
                u = parent[i][u];
            }
        }
        // cout << diff << endl;
        // cout << u << " " << v << endl;
 
        if(u == v) return u;
        for (int k = s - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
 
    ll query_dist(int u, int v) {
        int x = query_LCA(u,v);
        return dist[u]+dist[v]-2*dist[x];
    }
};