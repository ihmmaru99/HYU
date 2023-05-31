#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<vector<int>> adj(100);

    adj[1].push_back(3);
    adj[34].push_back(91);

    return 0;
}