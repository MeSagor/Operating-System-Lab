#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool haveCycle(int cur, vector<bool>& visited, vector<vector<int>>& graph) {
    visited[cur] = true;
    for (int x : graph[cur]) {
        if (!visited[x]) {
            return haveCycle(x, visited, graph);
        } else {
            return true;
        }
    }
    visited[cur] = false;

    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    vector<bool> visited(n + 1, false);
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    for (int i = 1; i < n + 1; i++) {
        if (!visited[i]) {
            bool have_cycle = haveCycle(i, visited, graph);
            if (have_cycle) {
                cout << endl << "Deadlock Found!" << endl;
                break;
            } else {
                cout << endl << "No Deadlock Found" << endl;
                break;
            }
        }
    }
}
