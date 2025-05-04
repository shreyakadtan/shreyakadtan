//Implement all the functions of a dictionary (ADT) using hashing and handle
//collisions using open addressing method (implement using linked list).
//Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be
//comparable, Keys must be unique.
//Standard Operations: Insert(key, value), Find(key), Delete(key)
// Implement all the functions of a dictionary (ADT) using hashing
// Collisions are handled using chaining (linked list at each index)

// Data: Set of (key, value) pairs, with unique keys
// Operations: Insert, Find, Delete

#include <iostream>
using namespace std;

// Node structure for linked list (used for chaining)
struct Node {
    int key, value;
    Node* next;

    // Constructor to initialize key-value pair
    Node(int k, int v) : key(k), value(v), next(0) {}
};

class Dict {
    // Array of pointers to Node (hash table of size 10)
    Node* table[10];

    // Simple hash function using modulo operator
    int hash(int k) { return k % 10; }

public:
    // Constructor to initialize hash table with null pointers
    Dict() {
        for (int i = 0; i < 10; i++) table[i] = 0;
    }

    // Insert a key-value pair into the hash table
    void insert(int k, int v) {
        int i = hash(k);  // Get hash index
        Node* p = table[i];

        // Check if key already exists; if so, update value
        while (p) {
            if (p->key == k) {
                p->value = v;
                return;
            }
            p = p->next;
        }

        // If key does not exist, create new node and insert at head
        Node* n = new Node(k, v);
        n->next = table[i];
        table[i] = n;
    }

    // Search for a key in the dictionary and print its value
    void find(int k) {
        int i = hash(k);
        Node* p = table[i];

        // Traverse linked list at index i
        while (p) {
            if (p->key == k) {
                cout << "Found: " << p->value << "\n";
                return;
            }
            p = p->next;
        }

        // Key not found
        cout << "Not found\n";
    }

    // Delete a key-value pair from the dictionary
    void del(int k) {
        int i = hash(k);
        Node *p = table[i], *prev = 0;

        // Traverse linked list to find the key
        while (p) {
            if (p->key == k) {
                // If node is found, remove it from the chain
                if (prev) prev->next = p->next;
                else table[i] = p->next;

                delete p;  // Free memory
                cout << "Deleted\n";
                return;
            }
            prev = p;
            p = p->next;
        }

        // Key not found
        cout << "Not found\n";
    }

    // Display contents of the hash table
    void show() {
        for (int i = 0; i < 10; i++) {
            cout << i << ": ";
            Node* p = table[i];

            // Print all nodes in the linked list at index i
            while (p) {
                cout << "(" << p->key << "," << p->value << ") ";
                p = p->next;
            }
            cout << "\n";
        }
    }
};

int main() {
    Dict d;
    int ch, k, v;

    // Menu-driven interface for dictionary operations
    do {
        cout << "\n1.Insert 2.Find 3.Delete 4.Show 5.Exit: ";
        cin >> ch;

        // Handle user choices
        if (ch == 1) {
            cout << "Key & Value: ";
            cin >> k >> v;
            d.insert(k, v);  // Insert key-value pair
        }
        else if (ch == 2) {
            cout << "Key: ";
            cin >> k;
            d.find(k);  // Find key
        }
        else if (ch == 3) {
            cout << "Key: ";
            cin >> k;
            d.del(k);  // Delete key
        }
        else if (ch == 4) {
            d.show();  // Display hash table
        }
    } while (ch != 5);  // Exit on choice 5

    return 0;
}
