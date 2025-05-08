#include <bits/stdc++.h>
using namespace std;

// DSU data structure
// path compression + rank by union
class DSU {
    int* parent;
    int* rank;

public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    // Union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            }
            else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            }
            else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

class Graph {
    vector<vector<int> > edgelist;
    int V;

public:
    Graph(int V) { this->V = V; }

    // Function to add edge in a graph
    void addEdge(int x, int y, int w)
    {
        edgelist.push_back({ w, x, y });
    }

    void kruskals_mst()
    {
        // Sort all edges
        sort(edgelist.begin(), edgelist.end());

        // Initialize the DSU
        DSU s(V);
        int ans = 0;
        int count = 0;  // To keep track of the number of edges in MST
        cout << "Following are the edges in the "
                "constructed MST\n";
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            // Take this edge in MST if it does
            // not form a cycle
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                ans += w;
                cout << x << " -- " << y << " == " << w << endl;
                count++;  // Increase the count of edges added to MST
            }
            if (count == V - 1) {
                break;
            }
        }
        cout << "Minimum Cost Spanning Tree: " << ans;
    }
};

// Driver code
int main()
{
    int V, E;

    // Take the number of vertices and edges as input
    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    // Create a graph object
    Graph g(V);

    // Take input for edges
    cout << "Enter the edges (x y w) where x and y are the vertices and w is the weight:\n";
    for (int i = 0; i < E; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        g.addEdge(x, y, w);
    }

    // Call Kruskal's algorithm
    g.kruskals_mst();

    return 0;
}