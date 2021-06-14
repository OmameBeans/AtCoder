void bfs(int s, vecveci &G, veci &dist) {
    dist[s] = 0;
    queue<int> q;
    q.push(s);

    while(!q.empty()) {
        int v = q.front();
        q.pop();

        for(int nv : G[v]) {
            if(dist[nv] != -1) continue;
            ist[nv] = dist[v] + 1;
            .push(nv);
        }
    }
}