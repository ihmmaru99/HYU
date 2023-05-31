#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

vector<vector<int>> adj(1001);
vector<bool> visit(1001, false);

void DFS(int current)
{
    visit[current] = true;
    cout << current << ' ';
    for (int i=0; i<int(adj[current].size()); i++){
        int next = adj[current][i];
        if(visit[next]) continue;
        DFS(next);
    }
}

void BFS(int start){
    queue<int> q;
    visit[start] = true;
    q.push(start);

    while (!q.empty()){
        int current = q.front();
        cout << current << ' ';
        q.pop();
        for (int i = 0; i < int(adj[current].size()); i++)
        {
            int next = adj[current][i];
            if(visit[next]) continue;
            visit[next] = true;
            q.push(next);
        }
    }
}

int main()
{
    int a, b, c;
    cin >> a >> b >> c;
    for (int i = 0; i<b; i++){
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i=1; i<=a; i++)
        sort(adj[i].begin(), adj[i].end());
    DFS(c);
    cout << '\n';
    for (int i = 1; i <=a; i++)
        visit[i] = false;
    BFS(c);
    cout << '\n';
    return 0;
}