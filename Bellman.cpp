#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void BellmanFord(const vector<Edge>& edges, int V, int source) {
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; ++i) {
        for (const Edge& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Check for negative-weight cycles
    for (const Edge& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative-weight cycle" << endl;
            return;
        }
    }

    // Print the shortest distances
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << "\t" << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter the source, destination, and weight of each edge:" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    BellmanFord(edges, V, source);

    return 0;
}

