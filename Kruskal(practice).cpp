#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Structure to represent an edge in the graph
struct Edge {
    char src, dest;
    int weight;
};

// Structure to represent a disjoint set
struct DisjointSet {
    unordered_map<char, char> parent;
    unordered_map<char, int> rank;

    DisjointSet(const vector<char>& vertices) {
        for (char v : vertices) {
            parent[v] = v;
            rank[v] = 0;
        }
    }

    // Find the root of the set to which the element belongs
    char find(char x) {
        if (parent[x] != x) {
            // Path compression: make the parent of x as the root
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union of two sets based on rank
    void unionSets(char x, char y) {
        char rootX = find(x);
        char rootY = find(y);

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
};

// Comparator function to sort edges by weight in non-decreasing order
bool compareEdges(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

// Function to find the minimum spanning tree using Kruskal's algorithm
vector<Edge> kruskalMST(const vector<Edge>& edges, const vector<char>& vertices, int& totalCost) {
    vector<Edge> result; // Stores the edges in the minimum spanning tree
    DisjointSet ds(vertices); // Create a disjoint set
    totalCost = 0; // Initialize the total cost to zero

    // Sort the edges in non-decreasing order of their weights
    vector<Edge> sortedEdges = edges;
    sort(sortedEdges.begin(), sortedEdges.end(), compareEdges);

    for (const Edge& edge : sortedEdges) {
        char srcRoot = ds.find(edge.src);
        char destRoot = ds.find(edge.dest);

        // If including the edge doesn't create a cycle, add it to the MST
        if (srcRoot != destRoot) {
            result.push_back(edge);
            ds.unionSets(srcRoot, destRoot);
            totalCost += edge.weight; // Add the weight of the edge to the total cost
        }
    }

    return result;
}

// Function to print the edges in the minimum spanning tree
void printMST(const vector<Edge>& MST) {
    cout << "Minimum Spanning Tree Edges:" << endl;
    for (const Edge& edge : MST) {
        cout << edge.src << " -- " << edge.dest << "  Weight: " << edge.weight << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter the number of vertices in the graph: ";
    cin >> V;
    cout << "Enter the number of edges in the graph: ";
    cin >> E;

    vector<Edge> edges(E);
    vector<char> vertices;
    cout << "Enter the source, destination, and weight of each edge:" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
        vertices.push_back(edges[i].src);
        vertices.push_back(edges[i].dest);
    }

    int totalCost;
    vector<Edge> MST = kruskalMST(edges, vertices, totalCost);
    printMST(MST);

    cout << "Total cost of the minimum spanning tree: " << totalCost << endl;

    return 0;
}

