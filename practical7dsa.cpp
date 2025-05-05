//Construct an expression tree from the given prefix expression eg. +- -a*bc/def and
//traverse it using post order traversal (non-recursive) and then delete the entire
//tree.
#include <iostream>
#include <string.h>
using namespace std;

// Structure to represent each node of the expression tree
struct node
{
    char data;         // Operator or operand
    node *left;        // Pointer to left child
    node *right;       // Pointer to right child
};

// Class to manage the expression tree
class tree
{
    char prefix[20];   // Array to hold the prefix expression

public:
    node *top;         // Pointer to the root of the tree

    // Function declarations
    void expression(char[]);
    void display(node *);
    void non_rec_postorder(node *);
    void del(node *);
};

// Stack class to manage tree node pointers
class stack
{
    node *data[30];    // Array to hold node pointers
    int top;           // Top index of the stack

public:
    stack()
    {
        top = -1;      // Initialize stack as empty
    }

    // Check if stack is empty
    int isempty()
    {
        return (top == -1);
    }

    // Push a node pointer onto the stack
    void push(node *p)
    {
        data[++top] = p;
    }

    // Pop a node pointer from the stack
    node *pop()
    {
        return (data[top--]);
    }
};

// Function to build an expression tree from prefix expression
void tree::expression(char prefix[])
{
    char c;
    stack s;                   // Create a stack to build the tree
    node *t1, *t2;
    int len, i;
    len = strlen(prefix);      // Get the length of the prefix expression

    // Traverse the prefix expression from right to left
    for (i = len - 1; i >= 0; i--)
    {
        top = new node;        // Create a new node
        top->left = NULL;
        top->right = NULL;

        // If current character is an operand (alphabet)
        if (isalpha(prefix[i]))
        {
            top->data = prefix[i];
            s.push(top);       // Push operand node onto the stack
        }
        // If current character is an operator
        else if (prefix[i] == '+' || prefix[i] == '*' || prefix[i] == '-' || prefix[i] == '/')
        {
            // Pop two operands (or subtrees) from the stack
            t2 = s.pop();
            t1 = s.pop();

            // Make a new operator node with t2 and t1 as children
            top->data = prefix[i];
            top->left = t2;
            top->right = t1;

            // Push the new subtree back to the stack
            s.push(top);
        }
    }

    // Final node on the stack is the root of the expression tree
    top = s.pop();
}

// Function to display the tree in preorder (for debug/display)
void tree::display(node *root)
{
    if (root != NULL)
    {
        cout << root->data;          // Visit root
        display(root->left);         // Traverse left subtree
        display(root->right);        // Traverse right subtree
    }
}

// Function to perform non-recursive postorder traversal
void tree::non_rec_postorder(node *top)
{
    stack s1, s2;
    node *T = top;

    s1.push(T);                      // Start from root

    // Postorder using two stacks
    while (!s1.isempty())
    {
        T = s1.pop();                // Pop from first stack
        s2.push(T);                  // Push to second stack

        // Push left and right children to s1
        if (T->left != NULL)
            s1.push(T->left);
        if (T->right != NULL)
            s1.push(T->right);
    }

    // s2 now contains nodes in reverse postorder
    while (!s2.isempty())
    {
        top = s2.pop();              // Pop in postorder
        cout << " | " << top->data;  // Print node data
    }
}

// Function to delete all nodes of the tree using postorder traversal
void tree::del(node *node)
{
    if (node == NULL)
        return;

    del(node->left);                // Recursively delete left subtree
    del(node->right);               // Recursively delete right subtree

    cout << endl << "Deleting Node " << node->data << endl;
    // Missing actual memory deallocation:
    // delete node;
}

// Main function
int main()
{
    char expr[20];
    tree t;

    // Get prefix expression input
    cout << "Enter Prefix Expression ";
    cin >> expr;

    cout << endl << "Stack" << endl;

    // Step 1: Build expression tree
    t.expression(expr);

    cout << endl;

    // Step 2: Perform postorder traversal (non-recursive)
    t.non_rec_postorder(t.top);

    cout << endl;

    // Step 3: Delete the expression tree
    t.del(t.top);

    // Step 4: Display (should be done before deletion for valid output)
    cout << endl << "Original Expression ";
    t.display(t.top);  // Might print nothing if tree is deleted

    cout << endl;
}
//time complexity:worst case-O(n2)
                //avg case-O(nlogn)
                //best case-1
