//15. Given sequence k = k1 <k2 < … < kn of n sorted keys, with a search probability pi
//for each key ki . Build the Binary search tree that has the least search cost given
//the access probability for each key.

// 15. Given sequence k = k1 < k2 < … < kn of n sorted keys,
// with a search probability pi for each key ki.
// Build the Binary Search Tree that has the least search cost
// given the access probability for each key.

// 15. Given sequence k = k1 < k2 < … < kn of n sorted keys,
// with a search probability pi for each key ki.
// Build the Binary Search Tree that has the least search cost
// given the access probability for each key.

#include<iostream>
#include<queue>
using namespace std;
#define max 10

class obst {
    // w: weight matrix, c: cost matrix, r: root matrix
    // a: keys, p: success probabilities, q: failure probabilities
    int w[max][max], r[max][max], c[max][max], a[max], p[max], q[max];
    int m, n, i, j, k;

public:
    void accept() {
        cout << "Enter the total no keys :";
        cin >> n;

        // Input sorted keys
        for(i = 0; i < n; i++) {
            cout << "\nEnter key :";
            cin >> a[i];
        }

        // Input probabilities of successful search for keys (1 to n)
        cout << "Enter probabilities of successful search :";
        for(i = 1; i <= n; i++) {
            cout << "\nEnter probability :";
            cin >> p[i];
        }

        // Input probabilities of unsuccessful search (0 to n)
        cout << "Enter probabilities of unsuccessful search :";
        for(i = 0; i <= n; i++) {
            cout << "\nEnter probability :";
            cin >> q[i];
        }
    }

    // Function to find the index of root that gives minimum cost
    int find(int i, int j) {
        int m, k;
        int min = 32000; // Assign a large value initially

        // Try all possible roots and find the one with minimum cost
        for(k = i + 1; k <= j; k++) {
            if((c[i][k-1] + c[k][j]) < min) {
                min = c[i][k-1] + c[k][j];
                m = k; // Store the best root index
            }
        }
        return m;
    }

    // Build the OBST using dynamic programming
    void build_obst() {
        // Case when j - i = 0 (empty subtrees)
        for(i = 0; i < n; i++) {
            w[i][i] = q[i];          // weight includes only unsuccessful search
            c[i][i] = r[i][i] = 0;   // no cost, no root
        }

        // Case when j - i = 1 (one key)
        for(i = 0; i < n; i++) {
            w[i][i+1] = p[i+1] + q[i+1] + w[i][i]; // total weight
            c[i][i+1] = w[i][i+1];                // cost equals weight
            r[i][i+1] = i + 1;                    // root is the key itself
        }

        // Initialize for last element
        w[n][n] = q[n];
        c[n][n] = r[n][n] = 0;

        // Case when j - i = 2, 3, ..., n (larger subtrees)
        for(m = 2; m <= n; m++) {
            for(i = 0; i <= n - m; i++) {
                j = i + m;
                w[i][j] = w[i][j-1] + p[j] + q[j];  // total weight of subtree
                k = find(i, j);                     // find root that minimizes cost
                c[i][j] = c[i][k-1] + c[k][j] + w[i][j]; // total cost
                r[i][j] = k;                         // store root
            }
        }
    }

    // Display the OBST structure and its cost
    void display() {
        queue<int> queue;
        int i, j, k;

        cout << "The Optimal Binary Search Tree For The Given Nodes is ....\n";
        cout << "\n The Root of this OBST is :: " << r[0][n];       // root of full tree
        cout << "\n The Cost Of this OBST is :: " << c[0][n];       // total cost
        cout << "\n\n\t  NODE\t  LEFT CHILD\t   RIGHT CHILD";
        cout << "\n -------------------------------------------------------";

        // Start from the whole tree
        queue.push(0);
        queue.push(n);

        // Level-order traversal to print nodes and children
        while(!queue.empty()) {
            i = queue.front(); queue.pop();
            j = queue.front(); queue.pop();
            k = r[i][j];  // root of subtree [i][j]

            cout << "\n         " << k;

            // Process left child
            if (r[i][k-1] != 0) {
                cout << "              " << r[i][k-1];
                queue.push(i);
                queue.push(k-1);
            } else {
                cout << "              -";
            }

            // Process right child
            if(r[k][j] != 0) {
                cout << "              " << r[k][j];
                queue.push(k);
                queue.push(j);
            } else {
                cout << "              -";
            }
        }
        cout << "\n";
    }
};

int main() {
    obst o;
    o.accept();      // Accept keys and probabilities
    o.build_obst();  // Build optimal binary search tree
    o.display();     // Display final OBST structure and cost
    return 0;
}
