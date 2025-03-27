#include<bits/stdc++.h>
using namespace std;

vector<int> shortestPath(vector<pair<int, int>> edges, int n, int m, int s, int t) {
    // Create adjacency list
    unordered_map<int, list<int>> adj;

    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].first;
        int v = edges[i].second;

        adj[u].push_back(v);
        adj[v].push_back(u);  // Since the graph is undirected
    }

    // Visited map to track the nodes
    unordered_map<int, bool> visited;

    // Parent map to track parent of each node
    unordered_map<int, int> parent;

    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // BFS to find the shortest path
    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (auto i : adj[node]) {
            if (!visited[i]) {
                visited[i] = true;
                parent[i] = node;
                q.push(i);
            }
        }
    }

    // Getting shortest path from parent map
    vector<int> ansPath;
    int currNode = t;
    ansPath.push_back(t);

    while (currNode != s) {
        currNode = parent[currNode];
        ansPath.push_back(currNode);
    }

    // Reversing the ans vector as we backtrack path from destination to source
    reverse(ansPath.begin(), ansPath.end());

    return ansPath;
}

int main() {
    int n, m, s, t;

    // Taking input for number of vertices (n) and edges (m)
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<pair<int, int>> edges(m);

    // Taking input for edges (u, v) of the graph
    cout << "Enter the edges (u v) where there is an edge from u to v:" << endl;
    for (int i = 0; i < m; i++) {
        cin >> edges[i].first >> edges[i].second;
    }

    // Taking input for the source and target nodes
    cout << "Enter the source node: ";
    cin >> s;
    cout << "Enter the target node: ";
    cin >> t;

    // Call the function to find the shortest path
    vector<int> path = shortestPath(edges, n, m, s, t);

    // Output the result
    if (path.empty() || path[0] != s) {
        cout << "No path found from " << s << " to " << t << endl;
    } else {
        cout << "Shortest path from " << s << " to " << t << ": ";
        for (int i : path) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
