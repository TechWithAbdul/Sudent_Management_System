#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <limits>
#include <stack>  // For stack handling
#include <queue>  // For queue handling

using namespace std;

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

class node {
public:
    int id, marksMatric, marksInter, entryTestMarks;
    string name, fn, phone, qualification, Course, address;
    node* next;
    double GPA;
};

class Admin {
public:
    string username;
    string password;

    Admin() : username("dsa"), password("1122") {}

    bool login() {
        string enteredUsername, enteredPassword;
        cout << "\n\t\t---------------------------------";
        cout << "\n\t\t| Admin Login |\n";
        cout << "\t\t---------------------------------\n";
        cout << "\t\t| Enter username: ";
        cin >> enteredUsername;
        cout << "\t\t| Enter password: ";
        cin >> enteredPassword;
        cout << "\t\t---------------------------------\n";
        return (enteredUsername == username && enteredPassword == password);
    }
};

class Student {
public:
    node* head = NULL;
    stack<node*> undoStack;  // Stack for undo functionality
    queue<node*> studentQueue;  // Queue for FIFO handling of students

    void loadRecords() {
        ifstream infile("studentsRECORD.txt");
        if (!infile) {
            cout << "\t\t| No existing records found. |" << endl;
            return;
        }

        int id, mMatric, mInter, entryTestMarks;
        string n, fn, c, q, ph, address;
        double GPA;
        while (infile >> id >> n >> fn >> c >> q >> mMatric >> mInter >> entryTestMarks >> GPA >> ph) {
            getline(infile, address);

            node* ne = new node;
            ne->id = id;
            ne->name = n;
            ne->fn = fn;
            ne->Course = c;
            ne->qualification = q;
            ne->phone = ph;
            ne->marksMatric = mMatric;
            ne->marksInter = mInter;
            ne->entryTestMarks = entryTestMarks;
            ne->GPA = GPA;
            ne->address = address;
            ne->next = head;
            head = ne;
            //  print out the ID of the student being added
            cout << "Added student with ID: " << id << endl;
        }
        infile.close();
    }

    void saveRecords() {
        ofstream outfile("studentsRECORD.txt");
        node* temp = head;
        while (temp != NULL) {
            outfile << temp->id << " " << temp->name << " " << temp->fn << " " << temp->Course << " "
                << temp->qualification << " " << temp->marksMatric << " " << temp->marksInter << " "
                << temp->entryTestMarks << " " << temp->GPA << " " << temp->phone << " " << temp->address << endl;
            temp = temp->next;
        }
        outfile.close();
    }

    void insert() {
        int i, mMatric, mInter, entryTestMarks;
        string n, c, q, ph, n2, address;

        cout << "\n\t\t---------------------------------";
        cout << "\n\t\t| Enter Student i.d: ";
        while (!(cin >> i)) {
            cout << "\t\t| Invalid input! Please enter a valid numeric Student ID: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin.ignore();
        cout << "\t\t| Enter Student name: ";
        getline(cin, n);
        cout << "\t\t| Enter Father name: ";
        getline(cin, n2);
        cout << "\t\t| Enter Course: ";
        getline(cin, c);
         cout << "\t\t| Enter Contact: ";
        getline(cin, ph);
        cout << "\t\t| Enter Address: ";
        getline(cin, address);
        cout << "\t\t| Enter student Qualification(matric/inter): ";
        getline(cin, q);

        while (q != "matric" && q != "inter") {
            cout << "\t\t| Invalid input! Please enter a valid qualification (matric/inter): ";
            getline(cin, q);
        }

        cout << "\t\t| Enter Marks in Matric: ";
        while (!(cin >> mMatric)) {
            cout << "\t\t| Invalid input! Please enter numeric marks for matric: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (q == "inter") {
            cout << "\t\t| Enter Marks in Intermediate: ";
            while (!(cin >> mInter)) {
                cout << "\t\t| Invalid input! Please enter numeric marks for intermediate: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        cout << "\t\t| Enter Entry Test Marks: ";
        while (!(cin >> entryTestMarks)) {
            cout << "\t\t| Invalid input! Please enter numeric entry test marks: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        double GPA = (mMatric * 0.1 + mInter * 0.2 + entryTestMarks * 0.7) / 100;
        
        node* ne = new node;
        ne->id = i;
        ne->name = n;
        ne->fn = n2;
        ne->Course = c;
        ne->qualification = q;
        ne->phone = ph;
        ne->marksMatric = mMatric;
        ne->marksInter = (q == "inter") ? mInter : 0;
        ne->entryTestMarks = entryTestMarks;
        ne->address = address;
        ne->GPA = GPA;

        undoStack.push(ne);
        studentQueue.push(ne);

        ne->next = head;
        head = ne;

        saveRecords();

        cout << "\n\t\t| New Record Inserted Successfully | " << endl;
    }

    void update() {
        int id;
        cout << "\n\t\t---------------------------------";
        cout << "\n\t\t| Enter Student ID to update: ";
        cin >> id;

        node* temp = head;
        while (temp != NULL && temp->id != id) {
            temp = temp->next;
        }

        if (temp != NULL) {
            cout << "\n\t\t| Record Found! |";
            int choice;
            do {
                cout << "\n\t\t---------------------------------";
                cout << "\n\t\t| What would you like to update? |";
                cout << "\n\t\t| 1. Name                        |";
                cout << "\n\t\t| 2. Father Name                 |";
                cout << "\n\t\t| 3. Course                      |";
                cout << "\n\t\t| 4. Marks                       |";
                cout << "\n\t\t| 5. Phone                       |";
                cout << "\n\t\t| 6. Address                     |";
                cout << "\n\t\t| 7. Exit                        |";
                cout << "\n\t\t---------------------------------";
                cout << "\n\t\t| Enter choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        cout << "\n\t\t| Enter new Name: ";
                        cin.ignore();  // Clear the input buffer
                        getline(cin, temp->name);
                        break;
                    case 2:
                        cout << "\n\t\t| Enter new Father Name: ";
                        cin.ignore();  // Clear the input buffer
                        getline(cin, temp->fn);
                        break;
                    case 3:
                        cout << "\n\t\t| Enter new Course: ";
                        cin.ignore();  // Clear the input buffer
                        getline(cin, temp->Course);
                        break;
                    case 4:
                        cout << "\n\t\t| Enter new Marks in Matric: ";
                        while (!(cin >> temp->marksMatric)) {
                            cout << "\t\t| Invalid input! Please enter numeric marks for matric: ";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }
                        if (temp->qualification == "inter") {
                            cout << "\n\t\t| Enter new Marks in Intermediate: ";
                            while (!(cin >> temp->marksInter)) {
                                cout << "\t\t| Invalid input! Please enter numeric marks for intermediate: ";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                        }
                        break;
                    case 5:
                        cout << "\n\t\t| Enter new Phone number: ";
                        cin.ignore();  // Clear the input buffer
                        getline(cin, temp->phone);
                        break;
                    case 6:
                        cout << "\n\t\t| Enter new Address: ";
                        cin.ignore();  // Clear the input buffer
                        getline(cin, temp->address);
                        break;
                    case 7:
                        return; // Exit the update menu
                    default:
                        cout << "\n\t\t| Invalid choice. Please try again. |";
                }
                temp->GPA = (temp->marksMatric * 0.1 + temp->marksInter * 0.2 + temp->entryTestMarks * 0.7) / 100;
            } while (true);
            saveRecords();
        } else {
            cout << "\n\t\t| Record with ID " << id << " not found. |";
        }
    }

    void deleteRecord() {
        int id;
        cout << "\n\t\t---------------------------------";
        cout << "\n\t\t| Enter Student ID to delete: ";
        cin >> id;

        node* temp = head;
        node* prev = NULL;
        while (temp != NULL && temp->id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp != NULL) {
            if (prev == NULL) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            saveRecords();
            cout << "\n\t\t| Record with ID " << id << " deleted successfully. |";
        } else {
            cout << "\n\t\t| Record with ID " << id << " not found. |";
        }
    }

    void sortByGPA() {
        if (head == NULL || head->next == NULL) return; // If list is empty or has only one student.

        bool swapped;
        node* current;
        node* prev = NULL;

        do {
            swapped = false;
            current = head;

            while (current->next != prev) {
                if (current->GPA < current->next->GPA) {
                    swap(current->id, current->next->id);
                    swap(current->name, current->next->name);
                    swap(current->fn, current->next->fn);
                    swap(current->Course, current->next->Course);
                    swap(current->qualification, current->next->qualification);
                    swap(current->marksMatric, current->next->marksMatric);
                    swap(current->marksInter, current->next->marksInter);
                    swap(current->entryTestMarks, current->next->entryTestMarks);
                    swap(current->GPA, current->next->GPA);
                    swap(current->phone, current->next->phone);
                    swap(current->address, current->next->address);
                    swapped = true;
                }
                current = current->next;
            }
            prev = current;
        } while (swapped);

        saveRecords();
    }

    void searchRecord() {
        int id;
        cout << "\n\t\t---------------------------------";
        cout << "\n\t\t| Enter Student ID to search: ";
        cin >> id;

        node* temp = head;
        while (temp != NULL) {
            if (temp->id == id) {
                cout << "\n\t\t---------------------------------";
                cout << "\n\t\t| Student ID: " << temp->id << endl;
                cout << "\t\t| Name: " << temp->name << endl;
                cout << "\t\t| Father Name: " << temp->fn << endl;
                cout << "\t\t| Course: " << temp->Course << endl;
                cout << "\t\t| Qualification: " << temp->qualification << endl;
                cout << "\t\t| Matric Marks: " << temp->marksMatric << endl;
                cout << "\t\t| Intermediate Marks: " << temp->marksInter << endl;
                cout << "\t\t| Entry Test Marks: " << temp->entryTestMarks << endl;
                cout << "\t\t| GPA: " << temp->GPA << endl;
                cout << "\t\t| Phone: " << temp->phone << endl;
                cout << "\t\t| Address: " << temp->address << endl;
                cout << "\t\t---------------------------------";
                return;
            }
            temp = temp->next;
        }

        cout << "\n\t\t| Record with ID " << id << " not found. |";
    }
    void showAllRecords() {
        node* temp = head;
        if (temp == NULL) {
            cout << "\n\t\t| No records found. |" << endl;
        } else {
            while (temp != NULL) {
                cout << "\n\t\t---------------------------------";
                cout << "\n\t\t| Student ID: " << temp->id;
                cout << "\n\t\t| Name: " << temp->name;
                cout << "\n\t\t| Father Name: " << temp->fn;
                cout << "\n\t\t| Course: " << temp->Course;
                cout << "\n\t\t| Qualification: " << temp->qualification;
                cout << "\n\t\t| Marks (Matric): " << temp->marksMatric;
                cout << "\n\t\t| Marks (Intermediate): " << temp->marksInter;
                cout << "\n\t\t| Entry Test Marks: " << temp->entryTestMarks;
                cout << "\n\t\t| GPA: " << temp->GPA;
                cout << "\n\t\t| Phone: " << temp->phone;
                cout << "\n\t\t| Address: " << temp->address;
                cout << "\n\t\t---------------------------------";
                temp = temp->next;
            }
        }
    }

    void count() {
        int count = 0;
        node* temp = head;
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        cout << "\t\t| Total records: " << count << " |\n";
    }
};

int main() {
    Student t;
    int choice;
    Admin admin;
    setColor(10);

    if (!admin.login()) {
        cout << "\n\t\t| Invalid login credentials. Exiting the program.\n";
        return 1;
    }

    t.loadRecords();

    char p;
    do {
        system("cls");
      cout << "\t\t-----------------------------------------" << endl;
        cout << "\t\t| \t\t WELCOME                |" << endl;
        cout << "\t\t-----------------------------------------" << endl;
        cout << "\t\t-----------------------------------------" << endl;
        cout << "\t\t| \tStudent Management System       |" << endl;
        cout << "\t\t-----------------------------------------" << endl;
        cout << "\t\t| 1. Add Students Record\t\t|" << endl;
        cout << "\t\t| 2. Update Student Record\t\t|" << endl;
        cout << "\t\t| 3. Delete Student Record\t\t|" << endl;
        cout << "\t\t| 4. Search Student Record\t\t|" << endl;
        cout << "\t\t| 5. Show Students Records\t\t|" << endl;
        cout << "\t\t| 6. Count All Records\t\t\t|" << endl;
        cout << "\t\t| 7. Sort by GPA\t\t\t|" << endl;
        cout << "\t\t| 8. EXIT\t\t\t\t|" << endl;
        cout << "\t\t-----------------------------------------" << endl;
        cout << "\t\t| Enter choice : ";
        cin >> choice;
        switch (choice) {
            case 1: system("cls"); t.insert(); break;
            case 2: system("cls"); t.update(); break;
            case 3: system("cls"); t.deleteRecord(); break;
            case 4: system("cls"); t.searchRecord(); break;
            case 5: system("cls"); t.showAllRecords(); break;
            case 6: system("cls"); t.count(); break;
            case 7: system("cls"); t.sortByGPA(); break;
            case 8: system("cls"); exit(0); break;
            default: cout << "\n\t\t| Invalid choice, please try again. |"; break;
        }
        cout << "\n\t\tWould you like to continue? (Y/N): ";
        cin >> p;
    } while (p == 'Y' || p == 'y');

    return 0;
}

