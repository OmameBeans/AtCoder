#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int dy[] = {-1,0,1,0};
int dx[] = {0,-1,0,1};

template <typename T>
struct grid_graph{
    vector<vector<T>> Graph;
    vector<vector<int>> dist;
    int H,W;
    grid_graph(int h,int w) : H(h),W(w){
        Graph = vector<vector<T>>(H,vector<T>(W));
        dist = vector<vector<int>>(H,vector<int>(W,-1));
    }

    //各マスの最短距離を出すよ！
    void bfs(int sy, int sx) {
        dist[sy][sx] = 0;
        queue<pair<int,int>> que;
        que.push({sy,sx});
        while(que.size()) {
            auto p = que.front();
            que.pop();
            int i = p.first;
            int j = p.second;
            for(int dir = 0; dir < 4; dir++) {
                int ni = i + dy[dir];
                int nj = j + dx[dir];
                if(ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
                if(Graph[ni][nj] == '#') continue;
                if(dist[ni][nj] == -1) {
                    dist[ni][nj] = dist[i][j] + 1;
                    que.push({ni,nj});
                }
            }
        }
    }

    void show_dist() {
        for(int i = 0; i < H; i++) {
            for(int j = 0; j < W; j++) {
                cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }

    void show_graph() {
        for(int i = 0; i < H; i++) {
            for(int j = 0; j < W; j++) {
                cout << Graph[i][j] << " ";
            }
            cout << endl;
        }
    }
};