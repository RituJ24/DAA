#include <bits/stdc++.h>
using namespace std;

#define V 4
#define INF 99999
int I;

void printSolution(int dist[][V]);
void floydWarshall(int dist[][V]) {
    int i, j, k;

    for (k = 0; k < V; k++) {
        printSolution(dist); // Print matrix after each node is added to the path
        cout << endl;

        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) &&
                    (dist[k][j] != INF && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

void printSolution(int dist[][V]) {
    cout << "The following matrix shows the shortest distances between every pair of vertices\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == I)
                cout << "I" << " ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int graph[V][V];
    cout << "Enter the matrix (use 'I' for infinity):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string input;
            cin >> input;
            if (input == "I")
                graph[i][j] = I;
            else {
                stringstream ss(input);
                ss >> graph[i][j];
            }
        }
    }

    floydWarshall(graph);
    return 0;
}
