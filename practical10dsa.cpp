//Consider telephone book database of N clients. Make use of a hash table
//implementation to quickly look up client‘s telephone number. Make use of Linear
//Probing technique to handle collision and compare them using number of
//comparisons required to find a set of telephone numbers

#include<iostream>
using namespace std;

#define MAX 10  // Define maximum size of the hash table

// Hash table class
class Hash
{
private:
    long int arr[MAX];  // Array to store telephone numbers

public:
    // Constructor to initialize all slots to -1 (empty)
    Hash()
    {
        for(int i = 0; i < MAX; i++)
        {
            arr[i] = -1;
        }
    }

    // Hash function: returns index using modulo operation
    int hashfun(long int a)
    {
        return (a % 10);  // Ensures index is between 0 and 9
    }

    // Insert a telephone number using linear probing
    void insert()
    {
        int index, count = 0;
        long int num;
        cout << "Enter telephone number: ";
        cin >> num;

        index = hashfun(num);  // Get index using hash function

        // Linear probing to find the next empty slot
        while (arr[index] != -1 && count < MAX)
        {
            index = (index + 1) % MAX;  // Move to next slot circularly
            count++;
        }

        if (count < MAX)
        {
            arr[index] = num;  // Insert the number
            cout << "Number inserted at index " << index << endl;
        }
        else
        {
            cout << "Hash table is FULL!" << endl;  // Table is full
        }
    }

    // Display the hash table contents
    void display()
    {
        for (int i = 0; i < MAX; i++)
        {
            if (arr[i] == -1)
                cout << i << " --> Empty" << endl;
            else
                cout << i << " --> " << arr[i] << endl;
        }
    }

    // Search for a telephone number using linear probing
    void search()
    {
        long int num;
        cout << "Enter telephone number to search: ";
        cin >> num;

        int index = hashfun(num);  // Start at hashed index
        int count = 0;

        // Search linearly for the number
        while (arr[index] != -1 && count < MAX)
        {
            if (arr[index] == num)
            {
                cout << "Number found at index " << index << endl;
                return;
            }
            index = (index + 1) % MAX;  // Move to next slot
            count++;
        }

        cout << "Number not found in the hash table." << endl;
    }
};

// Main function to interact with the hash table
int main()
{
    Hash h;  // Create hash table object
    int choice;

    // Menu-driven program
    while (true)
    {
        cout << "\n1. Insert to hash table" << endl;
        cout << "2. Display the hash table" << endl;
        cout << "3. Search from hash table" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
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
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}
// Operation Best Case	Worst Case
//           O(1)        O(n)
