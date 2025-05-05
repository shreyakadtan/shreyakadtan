//Represent a given graph using adjacency matrix to perform BFS using recursive
//method
#include <iostream>
#define max 100
using namespace std;

bool visited[max]; // Array to keep track of visited vertices
int adj[max][max]; // Adjacency matrix to represent the graph
int front = 0, rear = 0; // Indices for queue front and rear
int queue[max]; // Queue implementation using array

// Function to insert an element into the queue
void enqueue(int a) {
    if (rear < max) {
        queue[rear++] = a;
    }
}

// Function to remove and return the front element from the queue
int dequeue() {
    return queue[front++];
}

// Function to check if the queue is empty
bool isempty() {
    return (front == rear);
}

// Recursive BFS function
void bfs_recursive(int n) {
    if (isempty()) {
        return; // Base case: stop if queue is empty
    }
    int a = dequeue(); // Get the next vertex from the queue
    cout << a << " "; // Print the current vertex

    // Explore all adjacent vertices
    for (int i = 0; i < n; i++) {
        if (adj[a][i] == 1 && !visited[i]) { // Check for unvisited adjacent vertex
            enqueue(i); // Enqueue the adjacent vertex
            visited[i] = true; // Mark it as visited
        }
    }

    // Recurse with the next vertex in the queue
    bfs_recursive(n);
}

int main() {
    int start, n;

    cout << "Enter the number of vertices of the graph: ";
    cin >> n; // Input number of vertices

    cout << "Enter the Adjacency matrix:" << endl;
    for (int i = 0; i < n; i++) { // Input the adjacency matrix
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        visited[i] = false; // Initialize all vertices as unvisited
    }

    cout << "Enter the starting vertex of graph: ";
    cin >> start; // Input starting vertex

    enqueue(start); // Add starting vertex to queue
    visited[start] = true; // Mark starting vertex as visited

    bfs_recursive(n); // Start recursive BFS

    return 0;
}

//time complexity:O(V²)
