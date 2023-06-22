#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to find the vertex with the minimum distance value
int minDistance(vector<int>& dist, vector<bool>& visited, int V) {
    int minDist = INT_MAX, minIdx;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= minDist) { 
            minDist = dist[v]; 
            minIdx = v; 
        }
    }
    return minIdx;
}

// Function to print the shortest path from the source to the given vertex
void printPath(vector<int>& parent, int v) {
    if (parent[v] == -1) {
        cout << v;
        return;
    }
    printPath(parent, parent[v]);
    cout << " -> " << v;
}

// Function to perform Dijkstra's algorithm
void dijkstra(vector<vector<int> >& graph, int src) {
    int V = graph.size();
    vector<int> dist(V, INT_MAX);     // Stores the shortest distance from source to each vertex
    vector<bool> visited(V, false);   // Keeps track of visited vertices
    vector<int> parent(V, -1);        // Stores the parent vertex of each vertex in the shortest path
    dist[src] = 0;  // Distance from source to itself is 0

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited, V);
        visited[u] = true;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) { 
			//if there are new paths calculated and if we find a shorter path then we take that
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u; //toh parent will change to u because least distance
            }
        }
    }

    // Print the shortest path and distances from source to all vertices
    cout << "Vertex\tDistance\tPath" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "\t" << dist[i] << "\t\t";
        printPath(parent, i);
        cout << endl;
    }
}


int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;
    vector<vector<int> > graph(V, vector<int>(V, 0));
    cout << "Enter the adjacency matrix:" << endl;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;
    dijkstra(graph, source);
    return 0;
}
