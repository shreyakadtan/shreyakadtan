#include <iostream>
#include <string.h>
#define max 10  // Maximum size of the hash table
using namespace std;

// Structure for a node in the hash table
struct node {
    char name[15];     // Person's name
    long int mobno;    // Mobile number (used as key)
    int chain;         // Chain pointer for collision resolution

    // Constructor to initialize default/empty values
    node() {
        strcpy(name, "-");
        mobno = 0;
        chain = -1;
    }
};

// Hash table class using open addressing with linear probing and chaining
class hasht {
    node ht[max];  // Hash table array
public:
    int hashfun(long int);  // Hash function
    void insert();          // Insert a key-value pair
    void display();         // Display the hash table
    void search();          // Search for a key
    void del();             // Delete a key
};

// Hash function: simple modulo
int hasht::hashfun(long int num) {
    return (num % max);
}

// Insert a record using linear probing and maintain chaining
void hasht::insert() {
    int ind, prev;
    node S;

    cout << "Enter name and mobile number of a person:" << endl;
    cin >> S.name >> S.mobno;

    ind = hashfun(S.mobno);  // Get index using hash function

    // If slot is empty, insert directly
    if (ht[ind].mobno == 0) {
        ht[ind] = S;
    } else {
        // Collision: find next empty slot using linear probing
        prev = ind;
        while (ht[ind].mobno != 0) {
            ind = (ind + 1) % max;
        }
        ht[ind] = S;               // Insert at empty slot
        ht[prev].chain = ind;     // Link the previous record to new one
    }
}

// Display the contents of the hash table
void hasht::display() {
    cout << "Index\tName\t\tMobile Number\tChain" << endl;
    for (int i = 0; i < max; i++) {
        cout << i << "\t" << ht[i].name << "\t\t" << ht[i].mobno << "\t\t" << ht[i].chain << endl;
    }
}

// Search for a mobile number
void hasht::search(){
    long int num;
    int ind;
    cout << "Enter the number you want to search: ";
    cin >> num;

    ind = hashfun(num);  // Start from the hash index

    // Traverse chain until found or end of chain
    while(ind != -1){
        if(num == ht[ind].mobno){
            cout << "Mobile number is present at index: " << ind << endl;
            return;
        }
        ind = ht[ind].chain;
    }
    cout << "Record not found." << endl;
}

// Delete a mobile number
void hasht::del(){
    long int num;
    int ind, prev;
    cout << "Enter the number you want to delete: ";
    cin >> num;

    ind = hashfun(num);  // Get starting index from hash
    prev = -1;

    // Traverse the chain to find the key
    while(ind != -1){
        if(num == ht[ind].mobno){
            // If it's a leaf node in the chain
            if(ht[ind].chain == -1) {
                strcpy(ht[ind].name, "-");
                ht[ind].mobno = 0;
                cout << "Record is deleted";
            } else {
                // Copy next chained record into current
                int next = ht[ind].chain;
                ht[ind] = ht[next];

                // Clear next slot
                strcpy(ht[next].name, "-");
                ht[next].mobno = 0;
                ht[next].chain = -1;
            }

            // If there's a previous node, break its chain
            if(prev != -1)
                ht[prev].chain = -1;

            return;
        }

        prev = ind;
        ind = ht[ind].chain;  // Move to next node in chain
    }
    cout << "Record not found." << endl;
}

// Main function with menu for user interaction
int main(){
    int cho;
    hasht h;
    char a;

    do {
        cout << "1.Insert \n2.Display\n3.Search\n4.Delete\n5.Exit\nEnter your choice: ";
        cin >> cho;

        switch(cho){
            case 1:
                h.insert();
                break;
            case 2:
                h.display();
                break;
            case 3:
                h.search();
                break;
            case 4:
                h.del();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }

        cout << "Do you want to continue? (y/n): ";
        cin >> a;

    } while(a == 'y');  // ❌ Bug: should use `==`, not `=` (assignment)

    return 0;
}
