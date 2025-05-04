//Represent a given graph using adjacency matrix to perform BFS using recursive
//method
#include<iostream>
using namespace std;

const int MAX = 100; // Maximum number of vertices
int adj[MAX][MAX];   // Adjacency matrix to represent the graph
bool visited[MAX];   // Array to track visited vertices
int numVertices;     // Number of vertices in the graph

// Recursive function to perform BFS using a queue
void bfsrecursive(int queue[], int &front, int &rear) {
    // Base condition: If the queue is empty, return
    if (front > rear) {
        return;
    }

    // Dequeue the front element and process it
    int current = queue[front];
    front++;
    cout << current << " ";

    // Visit all unvisited adjacent vertices and enqueue them
    for (int i = 0; i < numVertices; i++) {
        if (adj[current][i] == 1 && !visited[i]) {
            visited[i] = true;
            rear++;
            queue[rear] = i;
        }
    }

    // Recursive call for the next element in the queue
    bfsrecursive(queue, front, rear);
}

// Function to initialize BFS and handle disconnected graphs
void bfs() {
    int queue[MAX];         // Array used as a queue
    int front = 0, rear = -1;

    // Initialize all vertices as unvisited
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    // Traverse all components of the graph (handles disconnected graphs)
    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) {
            // Start BFS from the unvisited node
            visited[i] = true;
            rear++;
            queue[rear] = i;

            // Start the recursive BFS
            bfsrecursive(queue, front, rear);
        }
    }
}

int main() {
    // Take user input for number of vertices
    cout << "Enter No. of vertices: ";
    cin >> numVertices;

    // Input the adjacency matrix
    cout << "Enter adjacency matrix:\n";
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            cin >> adj[i][j];
        }
    }

    // Perform BFS traversal
    cout << "BFS TRAVERSAL: ";
    bfs();

    return 0;
}
