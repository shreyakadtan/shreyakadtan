//Department maintains a student information. The file contains roll number, name,
//division and address. Allow user to add, delete information of student. Display
//information of particular student. If record of student does not exist an
//appropriate message is displayed. If it is, then the system displays the student
//details. Use sequential file to main the data.

#include<iostream>
#include<fstream> // for file handling
using namespace std;

// Class to hold student information
class student {
public:
    int rollno;
    string name;
    string div;
    string address;

    // Function to input student data from the user
    void setdata(){
        cout << "Enter roll number: ";
        cin >> rollno;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter division: ";
        cin >> div;
        cout << "Enter address: ";
        cin >> address;
    }

    // Function to display student data
    void getdata() {
        cout << "Roll No: " << rollno << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << div << endl;
        cout << "Address: " << address << endl;
    }
};

// Function to add a student record to the file
void addStudent() {
    student s;
    ofstream fout("studentdata.txt", ios::app); // Open file in append mode
    s.setdata(); // Take student input
    fout << s.rollno << " " << s.name << " " << s.div << " " << s.address << endl; // Write to file
    fout.close(); // Close the file
}

// Function to search for a student by roll number
void searchStudent() {
    int roll;
    bool found = false;
    cout << "Enter roll number to search: ";
    cin >> roll;

    ifstream fin("studentdata.txt"); // Open file for reading
    student s;

    // Read records line by line
    while(fin >> s.rollno >> s.name >> s.div >> s.address) {
        if(s.rollno == roll) {
            s.getdata(); // Display student data
            found = true;
            break;
        }
    }

    if(!found) {
        cout << "Record not found!" << endl;
    }
    fin.close(); // Close file
}

// Function to delete a student by roll number
void deleteStudent() {
    int roll;
    cout << "Enter roll number to delete: ";
    cin >> roll;

    ifstream fin("studentdata.txt"); // Original file
    ofstream fout("temp.txt");       // Temporary file

    student s;
    bool found = false;

    // Copy all records except the one to delete
    while(fin >> s.rollno >> s.name >> s.div >> s.address) {
        if(s.rollno != roll) {
            fout << s.rollno << " " << s.name << " " << s.div << " " << s.address << endl;
        } else {
            found = true; // Mark that the record was found
        }
    }

    fin.close();
    fout.close();

    remove("studentdata.txt");           // Delete original file
    rename("temp.txt", "studentdata.txt"); // Rename temp file as original

    if(found) {
        cout << "Record deleted!" << endl;
    } else {
        cout << "Record not found!" << endl;
    }
}

// Main menu-driven program
int main() {
    int choice;
    while(true) {
        // Menu options
        cout << "\n1. Add Student" << endl;
        cout << "2. Search Student" << endl;
        cout << "3. Delete Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
               addStudent();
               break;
            case 2:
               searchStudent();
               break;
            case 3:
               deleteStudent();
               break;
            case 4:
               return 0; // Exit the program
            default:
               cout << "Invalid choice!" << endl;
        }
    }
}
//Time Complexity:O(n)
