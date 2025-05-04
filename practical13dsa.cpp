//Implement all the functions of a dictionary (ADT) using hashing and handle
//collisions using: without replacement method.
//Data: Set of (key, value) pairs, Keys are mapped to values, Keys must be
//comparable, Keys must be unique.
//Standard Operations: Insert(key, value), Find(key), Delete(key)

#include<iostream>
#include<string.h>
#define max 10  // Define the size of the hash table

using namespace std;

// Structure representing one record in the hash table
struct node {
    char name[10];   // Person's name
    long int mn;     // Mobile number (used as key)
    int chain;       // Chain index for handling collisions

    // Constructor initializes empty values
    node() {
        mn = 0;
        chain = -1;
        strcpy(name, "-----");
    }
};

// Telephone class implementing dictionary ADT using hashing without replacement
class telephone {
public:
    node ht[max];   // Hash table of fixed size
    int count;      // Keeps track of how many elements are inserted

    // Constructor
    telephone() { count = 0; }

    int hashfun(long int);  // Hash function
    void insert();          // Insert operation
    void find();            // Find/Search operation
    void delno();           // Delete operation
    void display();         // Display table contents
};

// Hash function: returns index using modulo method
int telephone::hashfun(long int num) {
    return (num % 10);
}

// Insert function with collision handling using **without replacement**
void telephone::insert() {
    node s;
    int ind;
    cout << "Enter name and telephone number: \n";
    cin >> s.name >> s.mn;

    ind = hashfun(s.mn);  // Calculate hash index
    cout << "Index= " << ind << endl;

    // If table is nearly full, avoid infinite probing
    if(count == max - 1)
        cout << "Hash table full\n";

    // If calculated index is empty, directly insert
    if (ht[ind].mn == 0) {
        ht[ind] = s;
        count++;
    }
    // If index is occupied by a synonym (same hash value), add using chaining
    else if (ind == hashfun(ht[ind].mn)) {
        int prev = ind;
        int ch_ind = ind;

        // Probe to find an empty spot, keep track of the last synonym
        while (ht[ind].mn != 0) {
            if(ht[ind].chain != -1) {
                ind = ht[ind].chain;

                // Update chaining index if current entry is still a synonym
                if(prev == hashfun(ht[ind].mn)) {
                    ch_ind = ind;
                }
            }
            else
                ind = (ind + 1) % max;  // Linear probe to next slot
        }

        // Insert and update the chain link
        ht[ind] = s;
        ht[ch_ind].chain = ind;
        count++;
    }
    // If it's not a synonym (different key hashed to this spot), find another spot
    else {
        while (ht[ind].mn != 0)
            ind = (ind + 1) % max;  // Linear probing until empty spot found

        ht[ind] = s;
        count++;
    }
}

// Search for a telephone number
void telephone::find() {
    long int num;
    int cnt = 0;
    cout << "Enter the telephone number to search: ";
    cin >> num;

    int ind = hashfun(num);  // Start at hashed index

    // Follow the chain until the key is found or chain ends
    while (ind != -1) {
        cnt++;
        if (ht[ind].mn == num) {
            cout << "Record Found!\n";
            cout << "Name: " << ht[ind].name << "\tPhone: " << ht[ind].mn <<" found at index "<<ind<<" comparison "<<cnt<<endl;
            return;
        }
        ind = ht[ind].chain;  // Follow the chain
    }

    cout << "Record Not Found!\n";
}

// Delete a telephone number
void telephone::delno() {
    long int num;
    cout << "Enter the telephone number to delete: ";
    cin >> num;

    int ind = hashfun(num);  // Original hash index
    int oind = ind;
    int prev = -1;

    // Find the correct record using chain
    while (ind != -1) {
        // Skip records that don't hash to the same original index
        if (hashfun(ht[ind].mn) != oind)
            ind = (ind + 1) % max;
        else {
            if (ht[ind].mn == num) {
                cout << "Record Deleted!\n";

                // Shift chain forward if any
                while (ht[ind].chain != -1) {
                    int next = ht[ind].chain;

                    // Copy next node data to current and move ahead
                    ht[ind].mn = ht[next].mn;
                    strcpy(ht[ind].name, ht[next].name);
                    ht[ind].chain = ht[next].chain;

                    ind = next;  // Move to next node
                }

                // Clear the last node
                ht[ind].mn = 0;
                strcpy(ht[ind].name, "-----");
                ht[ind].chain = -1;
                return;
            }

            prev = ind;
            ind = ht[ind].chain;  // Move to next in chain
        }
    }

    cout << "Record Not Found!\n";
}

// Display the hash table contents
void telephone::display() {
    for (int i = 0; i < max; i++) {
        cout << i << "\t" << ht[i].name << "\t" << ht[i].mn << "\t" << ht[i].chain << endl;
    }
}

// Driver code: provides menu for testing
int main() {
    telephone t;
    int ch;
    char ans;

    do {
        cout << "Enter your choice" << endl;
        cout << "1.Insert" << endl;
        cout << "2.Display" << endl;
        cout << "3.Find" << endl;
        cout << "4.Delete" << endl;
        cin >> ch;

        switch (ch) {
            case 1: t.insert(); break;
            case 2: t.display(); break;
            case 3: t.find(); break;
            case 4: t.delno(); break;
            default: cout << "Invalid choice!!";
        }

        cout << "Do you want to continue? (1/0)";
        cin >> ans;
    } while (ans == '1');

    return 0;
}
