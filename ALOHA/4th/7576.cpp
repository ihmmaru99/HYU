#include <iostream>
#include <queue>
#include <algorithm>

#define MAX 101

using namespace std;

int N, M;
int arr[MAX][MAX];
int dist[MAX][MAX];
int dr[4] = {0,1,0,-1};
int dc[4] = {1,0,-1,0};

int main(){
    int M, N;
    cin >> M >> N;

    queue<pair<int, int>> q;
    for (int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> arr[i][j];
            if(arr[i][j] == 1){
                dist[i][j] = 0;
                q.push({i,j});
            }
        }
    }
    while(!q.empty()){
        int r = q.front().first, c = q.front().second;
        q.pop();
        for (int i=0; i<4; i++){
            int nr = r + dr[i], nc = c+dc[i];
            if(nr < 0 || nr >= N || nc < 0 || nc >=M) continue;
            if(arr[nr][nc] != 0) continue;
            if(dist[nr][nc] == MAX) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc}); 
        }
    }
    int ans = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(arr[i][j] != -1) ans = max(ans, dist[i][j]);
        }
    }
    if(ans == MAX) ans = -1;
    cout << ans;
}