#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int src, dest, weight;
};

// Structure to represent a subset for union-find
struct Subset {
    int parent, rank;
};

class Graph {
    int V;
    vector<Edge> edges;

public:
    Graph(int V) : V(V) {}

    // Function to add an edge to the graph
    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    // Utility function to find set of an element i
    int find(vector<Subset>& subsets, int i) {
        if (subsets[i].parent != i)
            subsets[i].parent = find(subsets, subsets[i].parent);
        return subsets[i].parent;
    }

    // Utility function to perform union of two subsets
    void Union(vector<Subset>& subsets, int x, int y) {
        int xroot = find(subsets, x);
        int yroot = find(subsets, y);

        if (subsets[xroot].rank < subsets[yroot].rank)
            subsets[xroot].parent = yroot;
        else if (subsets[xroot].rank > subsets[yroot].rank)
            subsets[yroot].parent = xroot;
        else {
            subsets[yroot].parent = xroot;
            subsets[xroot].rank++;
        }
    }

    // Function to find MST using Kruskal's algorithm
    void KruskalMST() {
        vector<Edge> result;
        int e = 0, i = 0;

        // Sort all the edges in non-decreasing order of their weight
        sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
            return a.weight < b.weight;
        });

        // Allocate memory for creating V subsets
        vector<Subset> subsets(V);
        for (int v = 0; v < V; v++) {
            subsets[v].parent = v;
            subsets[v].rank = 0;
        }

        // Number of edges to be taken is equal to V-1
        while (e < V - 1 && i < edges.size()) {
            Edge next_edge = edges[i++];
            int x = find(subsets, next_edge.src);
            int y = find(subsets, next_edge.dest);

            // If including this edge doesn't cause cycle, include it in result and increment the index of result for next edge
            if (x != y) {
                result.push_back(next_edge);
                Union(subsets, x, y);
                e++;
            }
        }

        // Print the edges of MST
        cout << "Minimum Spanning Tree edges:" << endl;
        for (i = 0; i < result.size(); ++i)
            cout << result[i].src << " - " << result[i].dest << "  Weight: " << result[i].weight << endl;
    }
};

int main() {
    // Create a graph
    Graph graph(4);
    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 6);
    graph.addEdge(0, 3, 5);
    graph.addEdge(1, 3, 15);
    graph.addEdge(2, 3, 4);

    // Find MST using Kruskal's algorithm
    graph.KruskalMST();

    return 0;
}