#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Function to find the vertex with the minimum key value
int findMinKey(const vector<int>& key, const vector<bool>& mstSet) {
    int minKey = INT_MAX;
    int minIndex = -1;

    for (int v = 0; v < key.size(); ++v) {
        if (!mstSet[v] && key[v] < minKey) {
            minKey = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to perform Prim's algorithm to find the minimum spanning tree
pair<vector<Edge>, int> primMST(const vector<vector<int>>& graph) {
    int V = graph.size();

    vector<Edge> MST(V);
    vector<int> key(V, INT_MAX);
    vector<bool> mstSet(V, false);

    // Start with the first vertex
    key[0] = 0;
    MST[0].src = -1;

    for (int count = 0; count < V - 1; ++count) {
        int u = findMinKey(key, mstSet);
        mstSet[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                MST[v].src = u;
                MST[v].dest = v;
                MST[v].weight = graph[u][v];
                key[v] = graph[u][v];
            }
        }
    }

    int totalCost = 0;
    for (int i = 1; i < V; ++i) {
        totalCost += MST[i].weight;
    }

    return make_pair(MST, totalCost);
}

// Function to print the minimum spanning tree and its cost
void printMST(const vector<Edge>& MST, int totalCost) {
    cout << "Minimum Spanning Tree:" << endl;
    for (const Edge& edge : MST) {
        if (edge.src != -1) {
            cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
        }
    }
    cout << "Total Cost: " << totalCost << endl;
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Enter the adjacency matrix:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cin >> graph[i][j];
        }
    }

    pair<vector<Edge>, int> result = primMST(graph);
    printMST(result.first, result.second);

    return 0;
}

