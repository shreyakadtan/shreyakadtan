//Read the marks obtained by students of second year in an online examination of
//particular subject. Find out maximum and minimum marks obtained in that
//subject. Use heap data structure. Analyze the algorithm.
//heap Sort

#include <iostream>
#define max 100  // Define a constant 'max' to set the size of the array
using namespace std;

class mar {
public:
    int arr[max], temp, n, left, right, largest, z;

    // Function declarations
    void create();  // Function to input marks and perform heap sort
    void hfy(int);   // Heapify function to maintain heap property
};

// ---------------- Heapify Function ---------------- //

/*
    The heapify function is used to maintain the heap property of the array.
    It ensures that the largest element is at the root of the subtree.
    If the subtree is not a valid heap, it swaps elements to restore the heap property.
*/
void mar::hfy(int i) {
    right = 2 * i + 2;  // Right child index
    left = 2 * i + 1;   // Left child index
    largest = i;         // Assume the root is the largest

    // If left child exists and is greater than the current largest, update largest
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child exists and is greater than the current largest, update largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If the largest element is not at the root, swap and heapify the affected subtree
    if (i != largest) {
        temp = arr[i];  // Swap current element with the largest element
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively call heapify to ensure the subtree maintains heap property
        hfy(largest);
    }
}

// ---------------- Create Function ---------------- //

/*
    The create function is responsible for:
    - Accepting the number of students and their marks as input.
    - Constructing the heap by calling heapify for each internal node starting from the bottom.
    - Performing heap sort to sort the marks.
    - Finding the maximum and minimum marks by utilizing the heap structure.
*/
void mar::create() {
    cout << "Enter the number of students:=" << endl;
    cin >> n;  // Input the number of students

    // Input the marks of the students
    for (int i = 0; i < n; i++) {
        cout << "Enter the marks for student no." << i + 1 << " :=" << endl;
        cin >> arr[i];  // Input marks for each student
    }

    // Build the max-heap by calling heapify on each internal node (starting from n/2 - 1)
    for (int i = (n / 2) - 1; i >= 0; i--) {
        hfy(i);  // Call heapify on each node
    }

    z = n;  // Store the initial size of the array (for later use)

    // Perform heap sort: extract the maximum element and rebuild the heap
    for (int i = n - 1; i >= 0; i--) {
        temp = arr[i];  // Swap the root (maximum element) with the last element
        arr[i] = arr[0];
        arr[0] = temp;

        n--;  // Reduce the size of the heap (exclude the last element)
        hfy(0);  // Restore the heap property after removing the root
    }

    // Output the maximum and minimum marks
    cout << "Maximum marks obtained in the subject:=" << endl;
    cout << arr[z - 1] << endl;  // The maximum marks will be at the last position after heap sort

    cout << "Minimum marks obtained in the subject:=" << endl;
    cout << arr[0] << endl;  // The minimum marks will be at the root after heap sort
}

// ---------------- Main Function ---------------- //

/*
    The main function creates an object of the 'mar' class and calls the 'create' function
    to input marks, perform heap sort, and display the maximum and minimum marks.
*/
int main() {
    mar ab;  // Create an object of the 'mar' class
    ab.create();  // Call the 'create' function to perform the operations
    return 0;  // Return 0 to indicate successful execution
}
