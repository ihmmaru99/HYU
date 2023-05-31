#include <iostream>
#include <algorithm>

int parent[201];

using namespace std;

int find(int x){
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);
}

void uni(int node_a, int node_b){
    int root_a = find(node_a);
    int root_b = find(node_b);
    if (root_a == root_b)
        return ;
    parent[root_b] = root_a;
    find(root_b);
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for (int i = 0; i <= 200; i++) parent[i] = i;
    int n, m;
    cin >> n;
    cin >> m;
    for(int i=1; i<=n; i++){
        for(int j = 1; j <= n; j++){
            int a;
            cin >> a;
            if (a == 1){
                uni(i, j);
            }
        }
    }
    int past;
    int cnt = 1;
    cin >> past;
    for (int i=1; i<m; i++){
        int now;
        cin >> now;
        if(find(past) == find(now))
            continue;
        else{
            cnt = 0;
            break;
        }
        past = now;
    }
    if (cnt)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}