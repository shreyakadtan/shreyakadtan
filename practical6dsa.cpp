//A book consists of chapters, chapters consist of sections and sections consist of
//subsections. Construct a tree and print the nodes. Find the time and space
//requirements of your method.

#include <iostream>
#include <string.h>
using namespace std;

// Structure to represent each node (book, chapter, section)
struct node
{
    string label;           // Stores the name (book title, chapter title, section title)
    int ch_count;           // Number of children (chapters for book, sections for chapter)
    struct node *child[10]; // Pointers to child nodes (up to 10 children)
} * root;                   // Root pointer for the book

// General Tree class to handle tree creation and display
class GT
{
public:
    void create_tree();         // Function to create the tree
    void display(node *r1);     // Function to display the tree hierarchy

    // Constructor initializes root to NULL
    GT()
    {
        root = NULL;
    }
};

// Function to create the book hierarchy tree
void GT::create_tree()
{
    int tchapters, i, j;
    root = new node; // Allocate memory for the book node

    // Input book title
    cout << "Enter name of book : ";
    cin.get();                    // To consume leftover newline character
    getline(cin, root->label);

    // Input number of chapters
    cout << "Enter number of chapters in book : ";
    cin >> tchapters;
    root->ch_count = tchapters;

    // Loop to input each chapter and its sections
    for (i = 0; i < tchapters; i++)
    {
        root->child[i] = new node; // Create new chapter node

        // Input chapter name
        cout << "Enter the name of Chapter " << i + 1 << " : ";
        cin.get(); // Consume newline
        getline(cin, root->child[i]->label);

        // Input number of sections in the chapter
        cout << "Enter number of sections in Chapter : " << root->child[i]->label << " : ";
        cin >> root->child[i]->ch_count;

        // Loop to input each section of the chapter
        for (j = 0; j < root->child[i]->ch_count; j++)
        {
            root->child[i]->child[j] = new node; // Create new section node

            // Input section name
            cout << "Enter Name of Section " << j + 1 << " : ";
            cin.get(); // Consume newline
            getline(cin, root->child[i]->child[j]->label);
        }
    }
}

// Function to display the hierarchy of the book
void GT::display(node *r1)
{
    int i, j;
    if (r1 != NULL)
    {
        cout << "\n-----Book Hierarchy---";
        cout << "\n Book title : " << r1->label;

        // Loop through each chapter
        for (i = 0; i < r1->ch_count; i++)
        {
            cout << "\nChapter " << i + 1;
            cout << " : " << r1->child[i]->label;

            // Display sections under this chapter
            cout << "\nSections : ";
            for (j = 0; j < r1->child[i]->ch_count; j++)
            {
                cout << "\n" << r1->child[i]->child[j]->label;
            }
        }
    }
    cout << endl;
}

// Main function to interact with user
int main()
{
    int choice;
    GT gt; // Create instance of GT class

    while (1) // Infinite loop until user exits
    {
        cout << "-----------------" << endl;
        cout << "Book Tree Creation" << endl;
        cout << "-----------------" << endl;
        cout << "1.Create" << endl;
        cout << "2.Display" << endl;
        cout << "3.Quit" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            gt.create_tree();  // Create the tree
            break;             // Prevent fall-through
        case 2:
            gt.display(root);  // Display the tree
            break;
        case 3:
            cout << "Thanks!!!";
            exit(1);           // Exit the program
        default:
            cout << "Wrong choice!!!" << endl;
        }
    }
    return 0;
}
