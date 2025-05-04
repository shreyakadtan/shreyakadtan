//Represent a given graph using adjacency matrix & perform DFS using recursive
//method.

// Represent a given graph using adjacency matrix & perform DFS using recursive method.

#include<iostream>
using namespace std;

// Maximum number of vertices
const int MAX = 100;

// Adjacency matrix to represent the graph
int adj[MAX][MAX];

// Array to keep track of visited vertices during DFS
int visited[MAX];

// Number of vertices in the graph
int numVertices;

// Recursive DFS function
void dfs(int vertex) {
    // Mark the current vertex as visited
    visited[vertex] = 1;

    // Print the visited vertex
    cout << vertex << " ";

    // Visit all adjacent unvisited vertices
    for(int i = 0; i < numVertices; i++) {
        if(adj[vertex][i] == 1 && !visited[i]) {
            dfs(i); // Recursive call for the adjacent vertex
        }
    }
}

int main() {
    // Input number of vertices in the graph
    cout << "Enter number of vertices: ";
    cin >> numVertices;

    // Input the adjacency matrix
    cout << "Enter adjacency matrix:" << endl;
    for(int i = 0; i < numVertices; i++) {
        for(int j = 0; j < numVertices; j++) {
            cin >> adj[i][j];
        }
    }

    // Start DFS traversal for all vertices
    // This handles disconnected components as well
    cout << "DFS TRAVERSAL: ";
    for(int i = 0; i < numVertices; i++) {
        if(!visited[i]) {
            dfs(i); // Start DFS from unvisited vertex
        }
    }

    return 0;
}
