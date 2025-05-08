#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Graph {
    int V; // number of vertices
    vector<vector<int>> graph; // adjacency matrix

public:
    Graph(int vertices) {
        V = vertices;
        graph = vector<vector<int>>(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int weight) {
        graph[u][v] = weight;
        graph[v][u] = weight; // undirected graph
    }

    void primMST() {
        vector<int> parent(V, -1);     // array to store MST
        vector<int> key(V, INT_MAX);   // values to pick minimum weight edge
        vector<bool> mstSet(V, false); // vertices included in MST

        // Start with first vertex
        key[0] = 0;

        // Construct MST with V vertices
        for (int count = 0; count < V - 1; count++) {
            // Pick vertex with minimum key value
            int minKey = INT_MAX;
            int u;
            for (int v = 0; v < V; v++) {
                if (!mstSet[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            mstSet[u] = true;

            // Update key values of adjacent vertices
            for (int v = 0; v < V; v++) {
                if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }

        // Print the MST
        cout << "\nEdges in the Minimum Spanning Tree:\n";
        cout << "Edge \tWeight\n";
        int totalWeight = 0;
        for (int i = 1; i < V; i++) {
            cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
            totalWeight += graph[i][parent[i]];
        }
        cout << "Total weight of MST: " << totalWeight << endl;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    
    Graph g(V);
    
    cout << "Enter number of edges: ";
    cin >> E;
    
    cout << "Enter edges and weights (format: source destination weight):\n";
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.primMST();
    return 0;
}