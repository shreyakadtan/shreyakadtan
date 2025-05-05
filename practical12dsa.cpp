// With Replacement

#include<iostream>
#include<string.h>
#define max 10
using namespace std;

// Node structure for the hash table
struct node {
    char name[10];     // Name of the person
    long int mn;       // Mobile number
    int chain;         // Chain pointer for collision resolution

    // Constructor initializes node to default values
    node() {
        mn = 0;
        chain = -1;
        strcpy(name, "-----");
    }
};

// Telephone directory class with hash table implementation
class telephone {
public:
    node ht[max];      // Hash table of size 'max'
    int count;         // Count of entries in the hash table

    telephone() { count = 0; }

    int hashfun(long int);  // Hash function
    void insert();          // Insert a new record
    void find();            // Search for a record
    void delno();           // Delete a record
    void display();         // Display all records
};

// Simple hash function: returns last digit of number
int telephone::hashfun(long int num) {
    return (num % 10);
}

// Insert a new record into the hash table
void telephone::insert() {
    node s;
    int index;

    cout <<"Enter name: \n";
    cin >> s.name;
    cout <<"Enter telephone number:\n";
    cin >> s.mn;

    index = hashfun(s.mn);  // Get hash index
    cout << "Index= " << index << endl;

    // Case 1: Slot is empty
    if (ht[index].mn == 0) {
        ht[index] = s;
        count++;
    }
    // Case 2: Collision, but same hash index (chain from original slot)
    else if (hashfun(ht[index].mn) == index) {
        int prev = index;
        while (ht[index].mn != 0) {
            if (ht[index].chain != -1)
                index = ht[index].chain;  // Follow the chain
            else {
                // Find next empty slot
                while (ht[index].mn != 0)
                    index = (index + 1) % max;
                ht[prev].chain = index;  // Link the previous chain to new index
            }
        }
        ht[index] = s;  // Insert new record
        count++;
    }
    // Case 3: Collision, but current record is not at its hash index
    else {
        int newIndex = index;
        while (ht[newIndex].mn != 0)
            newIndex = (newIndex + 1) % max;

        node temp = ht[index];    // Save the existing record
        ht[newIndex] = temp;      // Move old record to new location
        ht[index] = s;            // Insert new record at original index

        // Update the chain pointers
        int tempIndex = hashfun(temp.mn);
        while (ht[tempIndex].chain != index)
            tempIndex = ht[tempIndex].chain;
        ht[tempIndex].chain = newIndex;

        ht[index].chain = -1;  // New record doesn't have a chain
        count++;
    }
}

// Search for a telephone number in the hash table
void telephone::find() {
    long int num;
    int cnt = 0;
    cout << "Enter the telephone number to search: ";
    cin >> num;
    int index = hashfun(num);

    // Traverse through the chain
    while (index != -1) {
        cnt++;
        if (ht[index].mn == num) {
            cout <<"Record Found!\n";
            cout <<"Name: " << ht[index].name << endl;
            cout << "Phone: " << ht[index].mn << endl;
            cout << "Found at index: " << index << endl;
            cout << "Comparisons: " << cnt << endl;
            return;
        }
        index = ht[index].chain;  // Move to next in chain
    }
    cout << "Record Not Found!\n";
}

// Delete a telephone number from the hash table
void telephone::delno() {
    long int num;
    cout << "Enter the telephone number to delete: ";
    cin >> num;
    int index = hashfun(num);
    int prev = -1;

    // Traverse the chain to find the number
    while (index != -1) {
        if (ht[index].mn == num) {
            cout << "Record Deleted!\n";
            ht[index].mn = 0;
            strcpy(ht[index].name, "-----");
            if (prev != -1)
                ht[prev].chain = ht[index].chain;  // Update chain of previous
            ht[index].chain = -1;
            return;
        }
        prev = index;
        index = ht[index].chain;
    }
    cout << "Record Not Found!\n";
}

// Display all records in the hash table
void telephone::display() {
    for (int i = 0; i < max; i++) {
        cout << i << "\t" << ht[i].name << "\t" << ht[i].mn << "\t" << ht[i].chain << endl;
    }
}

int main() {
    telephone t;
    int ch;
    char ans;

    // Menu-driven program
    do {
        cout << "Enter your choice" << endl;
        cout << "1.Insert" << endl;
        cout << "2.Display" << endl;
        cout << "3.Search" << endl;
        cout << "4.Delete" << endl;
        cin >> ch;

        switch (ch) {
            case 1: t.insert();
                    break;
            case 2: t.display();
                    break;
            case 3: t.find();
                    break;
            case 4: t.delno();
                    break;
            default: cout << "Invalid choice!!";
        }

        cout << "Do you want to continue? (1/0)";
        cin >> ans;
    } while (ans == '1');

    return 0;
}

//complexity- O(n)

