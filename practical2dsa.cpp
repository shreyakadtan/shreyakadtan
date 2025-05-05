//Represent a given graph using adjacency matrix & perform DFS using nonrecursive method.
#include<iostream>
#include<stack>
using namespace std;

const int MAX = 100;

// Adjacency matrix to represent the graph
int adj[MAX][MAX];

// Visited array to keep track of visited vertices
bool visited[MAX];

// Number of vertices in the graph
int numVertices;

// Iterative DFS function using stack
void dfs() {
    stack<int> stack;

    // Initialize all vertices as unvisited
    for(int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }

    cout << "DFS TRAVERSAL:";

    // Traverse all vertices to handle disconnected graphs
    for(int i = 0; i < numVertices; i++) {
        // If vertex i is not visited, start DFS from it
        if(!visited[i]) {
            stack.push(i);       // Push starting vertex to the stack
            visited[i] = true;   // Mark as visited

            // Continue while stack is not empty
            while(!stack.empty()) {
                int current = stack.top();  // Get the top element
                stack.pop();                // Remove it from the stack
                cout << current << " ";     // Process the current vertex

                // Push all unvisited adjacent vertices to the stack
                // Iterate in reverse order to maintain correct DFS order
                for(int j = numVertices - 1; j >= 0; j--) {
                    if(adj[current][j] == 1 && !visited[j]) {
                        stack.push(j);       // Push neighbor to the stack
                        visited[j] = true;   // Mark neighbor as visited
                    }
                }
            }
        }
    }
    cout << endl;
}

int main() {
    // Take number of vertices as input
    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    // Input the adjacency matrix
    cout << "Enter the adjacency matrix:" << endl;
    for(int i = 0; i < numVertices; i++) {
        for(int j = 0; j < numVertices; j++) {
            cin >> adj[i][j];
        }
    }

    // Perform DFS traversal
    dfs();

    return 0;
}

//time complexity:O(V²)
