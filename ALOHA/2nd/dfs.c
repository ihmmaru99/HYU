#include <stdio.h>

int adj[101][101];
int visited[101];

void init(int n)
{
    for (int i = 1; i<=n; i++)
        visited[i] = 0;
}

void DFS(int start, int n)
{
    int current;
    visited[start] = 1;
    printf("%d ", start);
    for(int i = 1; i<= n; i++)
    {
        if(adj[start][i]){
            current = i;
            if(!visited[current])
                DFS(current, n);
        }
    }
}