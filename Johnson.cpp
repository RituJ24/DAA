#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int src, dest, weight;
};

void BellmanFord(const vector<Edge>& edges, int V, int source, vector<int>& dist) {
    dist.resize(V, INT_MAX);
    dist[source] = 0;

    for (int i = 0; i < V - 1; ++i) {
        for (const Edge& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
}

void Dijkstra(const vector<vector<int>>& graph, int source, vector<int>& dist) {
    int V = graph.size();
    dist.resize(V, INT_MAX);
    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

vector<vector<int>> Johnson(const vector<Edge>& edges, int V) {
    // Step 1: Add a new vertex and edges with weight 0 to all other vertices
    vector<Edge> modifiedEdges = edges;
    for (int i = 0; i < V; ++i) {
        Edge edge = {V, i, 0};
        modifiedEdges.push_back(edge);
    }

    // Step 2: Run Bellman-Ford algorithm to get the shortest distance from newVertex to all other vertices
    vector<int> h;
    BellmanFord(modifiedEdges, V + 1, V, h);

    // Step 3: Create the reweighted graph
    vector<vector<int>> graph(V, vector<int>(V, INT_MAX));
    for (const Edge& edge : edges) {
        int u = edge.src;
        int v = edge.dest;
        int weight = edge.weight;
        graph[u][v] = weight + h[u] - h[v];
    }

    // Step 4: Run Dijkstra's algorithm for each vertex to get the shortest paths
    vector<vector<int>> shortestPaths(V, vector<int>(V, INT_MAX));
    for (int src = 0; src < V; ++src) {
        Dijkstra(graph, src, shortestPaths[src]);
    }

    // Step 5: Restore the original edge weights by adjusting the shortest path distances
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (shortestPaths[i][j] != INT_MAX) {
                shortestPaths[i][j] = shortestPaths[i][j] - h[i] + h[j];
            }
        }
    }

    return shortestPaths;
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

    vector<vector<int>> shortestPaths = Johnson(edges, V);

    if (!shortestPaths.empty()) {
        cout << "Shortest path distances between vertices:" << endl;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (shortestPaths[i][j] == INT_MAX) {
                    cout << "INF ";
                } else {
                    cout << shortestPaths[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    return 0;
}

