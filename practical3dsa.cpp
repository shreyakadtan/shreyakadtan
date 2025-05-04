//Represent a given graph using adjacency list to perform BFS using non-recursive
//method.
#include<iostream>
using namespace std;

// Node structure for adjacency list
struct node {
	int vertex;
	node* next;
};

// Array of adjacency lists (graph representation)
node* adj[50];

// Global variables
int n, val, nb;

// Function to create the graph using adjacency list representation
void create_graph() {
	cout << "Enter how many nodes are there in graph: ";
	cin >> n;

	// Loop to take input for each node and its adjacent vertices
	for (int i = 1; i <= n; i++) {
		adj[i] = NULL;
		cout << "Enter value of " << i << ": ";
		cin >> val;

		node* nn = new node;
		node* last;

		nn->vertex = val;
		nn->next = NULL;

		// First node is added to the adjacency list
		adj[i] = last = nn;

		cout << "Enter how many nodes are connected to " << val << ": ";
		cin >> nb;

		// Loop to add all adjacent nodes
		for (int j = 1; j <= nb; j++) {
			cout << "Enter value of node: ";
			cin >> val;
			node* nn = new node;
			nn->vertex = val;
			nn->next = NULL;

			// Link the new node at the end of current list
			last->next = nn;
			last = nn;
		}
	}

	// Print the adjacency list representation of the graph
	cout << "Graph in adjacency list format:\n";
	for (int i = 1; i <= n; i++) {
		node* temp = adj[i];
		while (temp != NULL) {
			cout << temp->vertex << " -> ";
			temp = temp->next;
		}
		cout << "NULL" << endl;
	}
}

// Queue implementation using array for BFS
int arr[50];          // Queue array
int front = -1, rear = -1;

// Function to insert an element into the queue
void insertion(int m) {
	if (front == -1) {
		front = rear = 0;
	} else {
		rear++;
	}
	arr[rear] = m;
}

// Function to delete an element from the queue
int deletion() {
	int n;
	if ((front == -1 && rear == -1) || (front > rear)) {
		cout << "Queue is underflow!";
		return -1;
	} else {
		n = arr[front];
		front++;
	}
	return n;
}

// Function to check if queue is empty
bool isempty() {
	if ((front == -1 && rear == -1) || (front > rear))
		return true;
	else
		return false;
}

// Status constants for BFS
const int ready = 0, wait = 1, processed = 2;
int status[10];  // Array to track status of each vertex
int start;       // Root node for BFS

// Breadth-First Search function
void bfs() {
	// Initialize all vertices as ready (unvisited)
	for (int i = 1; i <= n; i++) {
		status[i] = ready;
	}

	cout << "Enter root node: ";
	cin >> start;

	// Start BFS by inserting root node into queue
	insertion(start);
	status[start] = wait;

	// Loop until queue is empty
	while (!isempty()) {
		int del = deletion();     // Dequeue a vertex
		if (del == -1) break;     // Exit if underflow
		status[del] = processed;  // Mark as processed
		cout << del << " ";       // Visit the node

		// Traverse all adjacent vertices
		node* temp = adj[del];
		while (temp != NULL) {
			int n = temp->vertex;

			// If the adjacent vertex is unvisited, enqueue it
			if (status[n] == ready) {
				insertion(n);
				status[n] = wait;
			}
			temp = temp->next;
		}
	}
}

// Main function
int main() {
	create_graph();  // Build the graph
	bfs();           // Perform BFS traversal
	return 0;
}
