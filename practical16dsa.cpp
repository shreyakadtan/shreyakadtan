//A Dictionary stores keywords & its meanings. Provide facility for adding new
//keywords and deleting keywords. Provide facility to display whole data sorted
//in ascending/ Descending order. Also find how many maximum comparisons
//may require for finding any keyword. Use Height balance tree and find the
//complexity for finding a keyword.

#include <iostream>
#include <cstring>
using namespace std;

// Structure representing a node in the AVL Tree
struct node {
    char word[20], mean[50];  // word and its meaning
    node *left, *right;       // pointers to left and right children
    int ht;                   // height of the node
};

class dict {
public:
    // Function declarations for various dictionary operations
    node* insert(node*, char[], char[]);     // Insert a new word into the tree
    node* deletion(node*, char[]);           // Delete a word from the tree
    void displayAscending(node*);            // Display all words in ascending order
    int height(node*);                       // Calculate the height of the tree
    int BF(node*);                           // Calculate the Balance Factor of the node
    node* LL(node*);                         // Left-Left Rotation (used for balancing)
    node* RR(node*);                         // Right-Right Rotation (used for balancing)
    node* LR(node*);                         // Left-Right Rotation (used for balancing)
    node* RL(node*);                         // Right-Left Rotation (used for balancing)
    int maxComparisons(node*);               // Find the maximum comparisons required for finding any keyword
};

// ------------------------ AVL Core Functions ------------------------ //

/*
    Calculates the height of the tree at a given node.
    Height of an empty tree is 0, and height of a node is 1 + maximum height of its left and right children.
*/
int dict::height(node *root) {
    if (!root) return 0;  // If root is null, height is 0
    int lh = root->left ? root->left->ht : 0;  // Left child height
    int rh = root->right ? root->right->ht : 0;  // Right child height
    return 1 + max(lh, rh);  // Height is 1 + max of left and right heights
}

/*
    Calculates the Balance Factor (BF) of the node.
    BF is the difference between the heights of the left and right subtrees.
    BF = left_height - right_height.
    If BF > 1, the tree is left heavy. If BF < -1, the tree is right heavy.
*/
int dict::BF(node *root) {
    if (!root) return 0;  // If root is null, BF is 0
    int lh = root->left ? root->left->ht : 0;  // Left child height
    int rh = root->right ? root->right->ht : 0;  // Right child height
    return lh - rh;  // Balance Factor is the difference between left and right subtree heights
}

/*
    Left-Left (LL) rotation:
    This is performed when the tree is left-heavy on the left side.
    The left child of the root becomes the new root, and the old root becomes the right child of the new root.
*/
node* dict::LL(node *x) {
    node *y = x->left;  // Left child becomes the new root
    x->left = y->right; // Left child’s right subtree becomes the left child of the old root
    y->right = x;       // Old root becomes the right child of the new root
    x->ht = height(x);  // Update the height of the old root
    y->ht = height(y);  // Update the height of the new root
    return y;            // Return the new root of the subtree
}

/*
    Right-Right (RR) rotation:
    This is performed when the tree is right-heavy on the right side.
    The right child of the root becomes the new root, and the old root becomes the left child of the new root.
*/
node* dict::RR(node *x) {
    node *y = x->right; // Right child becomes the new root
    x->right = y->left; // Right child’s left subtree becomes the right child of the old root
    y->left = x;        // Old root becomes the left child of the new root
    x->ht = height(x);  // Update the height of the old root
    y->ht = height(y);  // Update the height of the new root
    return y;            // Return the new root of the subtree
}

/*
    Left-Right (LR) rotation:
    This is performed when the tree is left-heavy on the right side.
    This rotation is a combination of a Left-Right rotation.
    First, a Right-Right rotation is performed on the left child of the root, followed by a Left-Left rotation on the root.
*/
node* dict::LR(node *T) {
    T->left = RR(T->left);  // First, perform a right-right rotation on the left child
    return LL(T);            // Then, perform a left-left rotation on the root
}

/*
    Right-Left (RL) rotation:
    This is performed when the tree is right-heavy on the left side.
    This rotation is a combination of a Right-Left rotation.
    First, a Left-Left rotation is performed on the right child of the root, followed by a Right-Right rotation on the root.
*/
node* dict::RL(node *T) {
    T->right = LL(T->right);  // First, perform a left-left rotation on the right child
    return RR(T);              // Then, perform a right-right rotation on the root
}

// ------------------------ Dictionary Operations ------------------------ //

/*
    Insert a new word into the AVL tree.
    If the word is smaller than the current node, it is inserted into the left subtree.
    If the word is greater, it is inserted into the right subtree.
    If the tree becomes unbalanced after insertion, appropriate rotations are performed.
*/
node* dict::insert(node *root, char w[], char m[]) {
    if (!root) {  // If the root is null, create a new node
        root = new node;
        strcpy(root->word, w);  // Copy the word into the node
        strcpy(root->mean, m);  // Copy the meaning into the node
        root->left = root->right = NULL;  // Set left and right children to NULL
        root->ht = 1;  // Height of a new node is 1
        return root;    // Return the newly created node
    }

    // Insert the word into the left or right subtree based on comparison
    if (strcmp(w, root->word) < 0) {  // If word is smaller than current node's word
        root->left = insert(root->left, w, m);
        if (BF(root) == 2)  // If the tree becomes left-heavy, perform balancing
            root = (strcmp(w, root->left->word) < 0) ? LL(root) : LR(root);
    } else if (strcmp(w, root->word) > 0) {  // If word is larger than current node's word
        root->right = insert(root->right, w, m);
        if (BF(root) == -2)  // If the tree becomes right-heavy, perform balancing
            root = (strcmp(w, root->right->word) > 0) ? RR(root) : RL(root);
    } else {
        cout << "Keyword already exists.\n";  // If the word already exists, notify the user
    }

    root->ht = height(root);  // Update the height of the current node
    return root;  // Return the updated node
}

/*
    Delete a word from the AVL tree.
    If the node to be deleted has one or no child, simply delete it.
    If the node has two children, find the in-order successor (the smallest node in the right subtree),
    replace the node with the successor, and delete the successor.
    After deletion, balance the tree if necessary.
*/
node* dict::deletion(node *T, char *w) {
    if (!T) return NULL;  // If the tree is empty, return NULL
    if (strcmp(w, T->word) < 0)  // If the word to delete is smaller, recurse to the left
        T->left = deletion(T->left, w);
    else if (strcmp(w, T->word) > 0)  // If the word to delete is larger, recurse to the right
        T->right = deletion(T->right, w);
    else {  // If the word is found
        if (!T->right) {  // If there is no right child, replace the node with the left child
            node *temp = T->left;
            delete T;
            return temp;
        }
        node *p = T->right;  // Find the in-order successor (smallest node in the right subtree)
        while (p->left) p = p->left;
        strcpy(T->word, p->word);  // Copy the successor’s word and meaning to the current node
        strcpy(T->mean, p->mean);
        T->right = deletion(T->right, p->word);  // Delete the successor node
    }

    T->ht = height(T);  // Update the height of the current node
    if (BF(T) == 2)  // If the tree becomes left-heavy, balance the tree
        T = (BF(T->left) >= 0) ? LL(T) : LR(T);
    else if (BF(T) == -2)  // If the tree becomes right-heavy, balance the tree
        T = (BF(T->right) <= 0) ? RR(T) : RL(T);
    return T;  // Return the updated tree
}

/*
    Display all the words in the dictionary in ascending order (in-order traversal).
    It first traverses the left subtree, then prints the current node, and then traverses the right subtree.
*/
void dict::displayAscending(node *root) {
    if (root) {
        displayAscending(root->left);  // Traverse left subtree
        cout << root->word << " : " << root->mean << endl;  // Print current node
        displayAscending(root->right);  // Traverse right subtree
    }
}

/*
    Calculate the maximum number of comparisons required to find a keyword.
    In the worst case, this is equal to the height of the tree.
*/
int dict::maxComparisons(node *root) {
    return height(root);  // The height of the tree gives the worst-case number of comparisons
}

// ------------------------ Main Program ------------------------ //

/*
    The main program allows the user to interact with the dictionary.
    The user can insert, delete, display words in ascending order,
    and check the maximum number of comparisons required to find a word.
*/
int main() {
    dict d;  // Create an object of the dict class
    node *root = NULL;  // Initialize the tree as empty
    int ch;
    char w[20], m[50];

    // Menu-driven loop for interacting with the dictionary
    do {
        cout << "\n\n===== DICTIONARY MENU =====";
        cout << "\n1. Add Word\n2. Delete Word\n3. Display Ascending\n";
        cout << "\n4. Max Comparisons\n8. Exit";
        cout << "\nEnter choice: ";
        cin >> ch;  // Take user input for the operation
        switch (ch) {
        case 1:
            cout << "Enter word: ";
            cin >> w;  // Input word to insert
            cout << "Enter meaning: ";
            cin.ignore();
            cin.getline(m, 50);  // Input meaning of the word
            root = d.insert(root, w, m);  // Insert the word into the tree
            break;
        case 2:
            cout << "Enter word to delete: ";
            cin >> w;  // Input word to delete
            root = d.deletion(root, w);  // Delete the word from the tree
            break;
        case 3:
            cout << "\nAscending Order:\n";
            d.displayAscending(root);  // Display words in ascending order
            break;

        case 4:
            cout << "Max comparisons required (tree height): " << d.maxComparisons(root) << endl;
            break;
        case 5:
            cout << "Exiting...\n";  // Exit the program
            break;
        default:
            cout << "Invalid choice!";  // Invalid input
        }
    } while (ch != 5);  // Continue until the user chooses to exit
    return 0;
}
