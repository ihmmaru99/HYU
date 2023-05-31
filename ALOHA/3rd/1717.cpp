#include <iostream>

int parent[1000001];
using namespace std;

int find(int x){
    if (x == parent[x])
        return x;
    return parent[x] = find(parent[x]);
}

void uni(int node_a, int node_b){
    int root_a = find(node_a);
    int root_b = find(node_b);

    parent[root_b] = root_a;
}

void result(int a, int b){
    int a_result = find(a);
    int b_result = find(b);
    if (a_result == b_result)
        cout << "YES" << '\n';
    else
        cout << "NO" << '\n';
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int m, n;
    cin >> n >> m;
    for(int i=0; i<=n; i++)
        parent[i] = i;
    for(int i = 0; i < m; i++){
        int c, a, b;
        cin >> c >> a >> b;
        if (c)
            result(a, b);
        else
            uni(a, b);
    }
}