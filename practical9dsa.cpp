//Beginning with an empty binary search tree, Construct binary search tree by
//inserting the values in the order given. After constructing a binary tree -
//i. Insert new node
//ii. Search a specific value in a tree
//iii. Change a tree so that the roles of the left and right pointers are swapped at
//every node

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int val) : data(val) {}
};

// Function to insert a node in the BST
Node* insert(Node* root, int value) {
    if (!root) return new Node(value);
    if (value < root->data) root->left = insert(root->left, value);
    else root->right = insert(root->right, value);
    return root;
}

// Function to search for a value in the tree
bool search(Node* root, int value) {
    if (!root) return false;
    if (root->data == value) return true;
    return (value < root->data) ? search(root->left, value) : search(root->right, value);
}

// Function to swap left and right pointers at every node
void swapChildren(Node* root) {
    if (!root) return;
    swap(root->left, root->right);  // Swap left and right children
    swapChildren(root->left);        // Recursively swap for the left subtree
    swapChildren(root->right);       // Recursively swap for the right subtree
}

// Function to display the tree in inorder traversal (for testing purposes)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

int main() {
    Node* root = nullptr;
    int n, value;

    cout << "Enter number of nodes: ";
    cin >> n;
    cout << "Enter the nodes: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }

    // Insert a new node
    cout << "Enter value to insert: ";
    cin >> value;
    root = insert(root, value);

    // Search for a specific value
    cout << "Enter value to search: ";
    cin >> value;
    cout << (search(root, value) ? "Found" : "Not Found") << endl;

    // Inorder traversal before swap
    cout << "Inorder traversal before swap: ";
    inorder(root);
    cout << endl;

    // Swap the left and right children at each node
    swapChildren(root);

    // Inorder traversal after swap
    cout << "Inorder traversal after swap: ";
    inorder(root);
    cout << endl;

    return 0;
}

//Best Case (Balanced BST):O(nlogn)
​//Worst Case (Skewed BST):O(n 2)
