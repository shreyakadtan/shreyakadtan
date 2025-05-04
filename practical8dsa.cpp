//Beginning with an empty binary search tree, Construct binary search tree by
//inserting the values in the order given. After constructing a binary tree -
// i. Insert new node
//ii. Find number of nodes in longest path from root
//iii. Minimum data value found in the tree

#include <iostream>
#include <algorithm>
using namespace std;

// Structure to define a node in the binary search tree
struct Node {
    int data;          // Value of the node
    Node* left = nullptr;   // Pointer to the left child
    Node* right = nullptr;  // Pointer to the right child
    Node(int val) : data(val) {}  // Constructor to initialize a node
};

// Function to insert a new value into the BST
Node* insert(Node* root, int value) {
    if (!root) return new Node(value); // If tree is empty, create a new node
    if (value < root->data)
        root->left = insert(root->left, value);  // Insert in left subtree if smaller
    else
        root->right = insert(root->right, value); // Insert in right subtree if greater or equal
    return root;  // Return the unchanged root pointer
}

// Function to find the minimum value in the BST
int findMin(Node* root) {
    while (root && root->left)
        root = root->left;  // Keep going left to find the smallest value
    return root ? root->data : -1;  // Return the data or -1 if tree is empty
}

// Function to find the length of the longest path from the root to a leaf
int longestPath(Node* root) {
    if (!root) return 0;  // If node is null, path length is 0
    // Recursively find the longest path in left and right subtrees and add 1 for current node
    return max(longestPath(root->left), longestPath(root->right)) + 1;
}

int main() {
    Node* root = nullptr;  // Start with an empty BST
    int n, value;

    // Get number of nodes to insert initially
    cout << "Enter number of nodes: ";
    cin >> n;

    // Read node values and insert into BST
    cout << "Enter the nodes: ";
    while (n--) {
        cin >> value;
        root = insert(root, value);
    }

    // Insert a new node value
    cout << "Enter new value to insert: ";
    cin >> value;
    root = insert(root, value);

    // Output the length of the longest path from root to a leaf
    cout << "Longest path from root: " << longestPath(root) << endl;

    // Output the minimum value found in the BST
    cout << "Minimum value in the tree: " << findMin(root) << endl;

    return 0;
}
