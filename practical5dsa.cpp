//There are flight paths between cities. If there is a flight between city A and city B
//then there is an edge between the cities. The cost of the edge can be the time that
//flight takes to reach city B from A or the amount of fuel used for the journey.
//Represent this as a graph. The node can be represented by airport name or name of
//the city. Use adjacency list representation of the graph or use adjacency matrix
//representation of the graph. Check whether the graph is connected or not. Justify
//the storage representation used.

#include<iostream>
#include<queue>
using namespace std;

// Class to represent the flight graph
class graph
{
public:
    string city[5];   // Array to store city names
    int M[5][5];      // Adjacency matrix to store flight times between cities
    int n;            // Number of cities

    // Constructor: Takes number of cities as input
    graph()
    {
        cout << "\nEnter number of cities :";
        cin >> n;
    }

    // Function to initialize adjacency matrix to 0 (no flights)
    void initialize()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                M[i][j] = 0;
            }
        }
    }

    // Function to create graph by inputting cities and flight times
    void create()
    {
        int a, b;
        char s[10], d[10], ch;

        // Input city names
        for(int i = 0; i < n; i++)
        {
            cout << "Enter city name: ";
            cin >> city[i];
        }

        // Input flight connections repeatedly
        do {
            cout << "Enter the starting city: ";
            cin >> s;

            // Find index of source city
            int i = 0;
            while(city[i] != s)
            {
                i++;
            }
            a = i;

            cout << "Enter the destination city: ";
            cin >> d;

            // Find index of destination city
            i = 0;
            while(city[i] != d)
            {
                i++;
            }
            b = i;

            // Input flight time (cost of edge)
            cout << "Enter amount of time required: ";
            cin >> M[a][b];

            // Since the graph is undirected, mirror the edge
            M[b][a] = M[a][b];

            // Ask user whether to continue adding edges
            cout << "Enter 'y' to add more cities or 'n' to stop and display matrix: ";
            cin >> ch;

        } while(ch == 'y'); // Loop ends when user inputs 'n'
    }

    // Function to display adjacency matrix of the graph
    void display()
    {
        // Print city names as column headers
        for(int i = 0; i < n; i++)
        {
            cout << city[i] << " ";
        }
        cout << "\n";

        // Print each row: city name followed by flight times to other cities
        for(int i = 0; i < n; i++)
        {
            cout << city[i] << " ";
            for(int j = 0; j < n; j++)
            {
                cout << M[i][j] << " ";
            }
            cout << "\n";
        }
    }

    // Function to check whether the graph is connected
    void connected()
    {
        int flag = 0;

        // Naive check: if any two distinct cities have no direct connection
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(i != j && M[i][j] == 0 && M[j][i] == 0)
                {
                    flag = 1; // Found a pair not directly connected
                    break;
                }
            }
        }

        // Display connectivity result based on the check
        if(flag == 0)
        {
            cout << "\nGraph is connected";
        }
        else
        {
            cout << "\nGraph is not connected";
        }
    }
};

// Main function
int main()
{
    graph g;          // Create graph object
    g.initialize();   // Initialize adjacency matrix
    g.create();       // Build the graph from user input
    g.display();      // Display the graph
    g.connected();    // Check if the graph is connected
    return 0;
}
