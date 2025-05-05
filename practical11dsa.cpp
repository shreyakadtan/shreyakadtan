//Consider telephone book database of N clients. Make use of a hash table
//implementation to quickly look up client‘s telephone number. Make use of
//Quadratic Probing technique to handle collision and compare them using number
//of comparisons required to find a set of telephone numbers

#include<iostream>
using namespace std;
const int MAX = 10;

// Hash table class using Quadratic Probing
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

    // Hash function to compute index
    int hashfun(long int a)
    {
        return (a % MAX);
    }

    // Insert a telephone number using Quadratic Probing
    void insert()
    {
        long int num;
        cout << "Enter telephone number: ";
        cin >> num;

        int index = hashfun(num);
        int i = 0;

        // Quadratic probing: check index + i^2
        while (arr[index] != -1 && i < MAX)
        {
            index = (hashfun(num) + i * i) % MAX;
            i++;
        }

        if (i < MAX)
        {
            arr[index] = num;  // Insert number at calculated index
            cout << "Number inserted at index " << index << endl;
        }
        else
        {
            cout << "Hash table is FULL!" << endl;
        }
    }

    // Display the hash table
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

    // Search for a telephone number using Quadratic Probing
    void search()
    {
        long int num;
        cout << "Enter telephone number to search: ";
        cin >> num;

        int index = hashfun(num);
        int i = 0;

        // Quadratic probing search
        while (arr[index] != -1 && i < MAX)
        {
            if (arr[index] == num)
            {
                cout << "Number " << num << " found at index " << index << endl;
                return;
            }
            index = (hashfun(num) + i * i) % MAX;
            i++;
        }

        cout << "Number " << num << " does not exist in the hash table." << endl;
    }
};

// Main function for menu-driven program
int main()
{
    Hash h;
    int choice;

    while (true)
    {
        cout << "1. Insert" << endl;
        cout << "2. Display" << endl;
        cout << "3. Search" << endl;
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
// time complexity: O(n) 
