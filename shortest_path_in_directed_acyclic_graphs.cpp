#include<iostream>
#include<unordered_map>
#include<list>
#include<stack>
#include<vector>
#include<limits.h>

using namespace std;

class Graph {
    public:
    // Adjacency list representation of the graph
    unordered_map<int, list<pair<int, int>>> adj;

    // Function to add an edge to the graph
    void addEdge(int u, int v, int weight) {
        pair<int, int> p = make_pair(v, weight);
        adj[u].push_back(p);  // Add an edge from u to v with the given weight
    }

    // Function to print the adjacency list of the graph
    void printAdjList() {
        for (auto i : adj) {
            cout << i.first << " -> ";  // Print the current node
            for (auto j : i.second) {
                cout << "(" << j.first << ", " << j.second << "), ";  // Print each neighbor and its weight
            }
            cout << endl;
        }
    }

    // Depth-First Search (DFS) to perform topological sorting
    void dfs(int node, unordered_map<int, bool> &visited, stack<int> &st) {
        visited[node] = true;  // Mark the current node as visited

        // Recur for all the neighbors of the current node
        for (auto neighbour : adj[node]) {
            if (!visited[neighbour.first]) {
                dfs(neighbour.first, visited, st);  // Recursive call for unvisited neighbors
            }
        }

        st.push(node);  // Push the current node to the stack after visiting all its neighbors
    }

    // Function to get the shortest path from the source node using the distances
    void getShortestPath(int src, vector<int> &dist, stack<int> &st) {
        dist[src] = 0;  // Distance to the source node is 0

        // Process nodes in topologically sorted order
        while (!st.empty()) {
            int node = st.top();  // Get the top node from the stack
            st.pop();  // Remove the node from the stack

            // Update the distance for each neighbor of the current node
            if (dist[node] != INT_MAX) {
                for (auto i : adj[node]) {
                    if (dist[node] + i.second < dist[i.first]) {
                        dist[i.first] = dist[node] + i.second;  // Relax the edge
                    }
                }
            }
        }
    }
};

int main() {
    Graph g;

    int n, m;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> m;

    // Adding edges to the graph based on user input
    cout << "Enter " << m << " edges (u v weight) for the graph:" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        g.addEdge(u, v, weight);
    }

    // Printing the adjacency list to see the graph structure
    cout << "Adjacency List of the graph:" << endl;
    g.printAdjList();

    // Topological sort initialization
    unordered_map<int, bool> visited;
    stack<int> st;

    // Perform DFS for each node to get the topological order
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            g.dfs(i, visited, st);
        }
    }

    // Taking input for the source node for shortest path calculation
    int src;
    cout << "Enter the source node for shortest path calculation: ";
    cin >> src;

    vector<int> dist(n, INT_MAX);  // Initialize distances with infinity
    g.getShortestPath(src, dist, st);  // Compute shortest paths from the source node

    // Print the shortest path distances
    cout << "The shortest path distances from source " << src << " are: ";
    for (auto i : dist) {
        if (i == INT_MAX)
            cout << "INF ";  // INF indicates that the node is unreachable
        else
            cout << i << " ";  // Print distance of each node from the source
    }
    cout << endl;

    return 0;
}
