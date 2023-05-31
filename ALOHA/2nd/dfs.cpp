#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj(100);
vector<bool> visit(100, false);

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