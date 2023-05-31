#include <iostream>
#include <queue>
#include <vector>

using namespace std;
vector<vector<int>> adj(100);
vector<bool> visit(100, false);

void BFS(int start){
    queue<int> q;
    visit[start] = true;
    q.push(start);

    while (!q.empty()){
        int current = q.front();
        cout << current << ' ';
        q.pop();
    
        for (int i = 0; i < int(adj[current].size()); ++i)
        {
            int next = adj[current][i];
            if(visit[next]) continue;
            visit[next] = true;
            q.push(next);
        }
    }
}