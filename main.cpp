#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
using namespace std;

class Student {
private:
    int id;
    string name, course;
    float marks;

public:
    Student(int i, string n, string c, float m) {
        id = i;
        name = n;
        course = c;
        marks = m;
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getCourse() const { return course; }
    float getMarks() const { return marks; }

    void update(string n, string c) {
        name = n;
        course = c;
    }

    void setMarks(float m) {
        if (m < 0 || m > 100)
            throw invalid_argument("Marks must be 0 to 100.");
        marks = m;
    }

    float percentage() const {
        return marks;
    }

    string grade() const {
        if (marks >= 90) return "A+";
        if (marks >= 80) return "A";
        if (marks >= 70) return "B";
        if (marks >= 60) return "C";
        if (marks >= 40) return "D";
        return "Fail";
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(15) << course
             << setw(10) << marks
             << grade() << endl;
    }
};

vector<Student> students;
const string FILE_NAME = "students.csv";

// Search student by ID
int findStudent(int id) {
    for (int i = 0; i < (int)students.size(); i++) {
        if (students[i].getId() == id)
            return i;
    }
    return -1;
}

// Save records into file
void saveData() {
    ofstream file(FILE_NAME);

    if (!file)
        throw runtime_error("Unable to open data file.");

    for (const auto& s : students) {
        file << s.getId() << ","
             << s.getName() << ","
             << s.getCourse() << ","
             << s.getMarks() << "\n";
    }

    file.close();
}

// Load records from file
void loadData() {
    ifstream file(FILE_NAME);
    if (!file) return;

    students.clear();
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, course, marks;

        if (getline(ss, id, ',') &&
            getline(ss, name, ',') &&
            getline(ss, course, ',') &&
            getline(ss, marks, ',')) {

            try {
                int i = stoi(id);
                float m = stof(marks);

                if (i > 0 && m >= 0 && m <= 100 &&
                    findStudent(i) == -1) {
                    students.emplace_back(i, name, course, m);
                }
            }
            catch (...) {
                cerr << "Invalid record skipped.\n";
            }
        }
    }
    file.close();
}

// Add student
void addStudent() {
    int id;
    string name, course;
    float marks;

    cout << "Enter Student ID: ";
    cin >> id;

    if (cin.fail() || id <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID!\n";
        return;
    }

    if (findStudent(id) != -1) {
        cout << "Student ID already exists!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Course: ";
    getline(cin, course);

    cout << "Enter Marks (0-100): ";
    cin >> marks;

    if (cin.fail() || marks < 0 || marks > 100) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Marks!\n";
        return;
    }

    students.emplace_back(id, name, course, marks);
    saveData();

    cout << "Student Added Successfully!\n";
}

// Display all students
void displayStudents() {
    if (students.empty()) {
        cout << "No Student Records Found.\n";
        return;
    }

    cout << "\nID        Name                Course         Marks     Grade\n";
    cout << "------------------------------------------------------------\n";

    for (const auto& s : students)
        s.display();
}

// Search student
void searchStudent() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
    } else {
        cout << "\nStudent Details:\n";
        students[index].display();
    }
}

// Update student
void updateStudent() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    string name, course;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter New Name: ";
    getline(cin, name);

    cout << "Enter New Course: ";
    getline(cin, course);

    students[index].update(name, course);
    saveData();

    cout << "Record Updated Successfully!\n";
}

// Delete student
void deleteStudent() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    students.erase(students.begin() + index);
    saveData();

    cout << "Student Deleted Successfully!\n";
}

// Update marks
void addMarks() {
    int id;
    float marks;

    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    cout << "Enter New Marks (0-100): ";
    cin >> marks;

    try {
        if (cin.fail()) {
            throw invalid_argument("Enter numeric marks.");
        }

        students[index].setMarks(marks);
        saveData();

        cout << "Marks Updated Successfully!\n";
    }
    catch (const exception& e) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: " << e.what() << endl;
    }
}

// Calculate result
void calculateResult() {
    int id;
    cout << "Enter Student ID: ";
    cin >> id;

    int index = findStudent(id);

    if (index == -1) {
        cout << "Student Not Found!\n";
        return;
    }

    Student s = students[index];

    cout << "\n----- STUDENT RESULT -----\n";
    cout << "Name       : " << s.getName() << endl;
    cout << "Course     : " << s.getCourse() << endl;
    cout << "Percentage : " << s.percentage() << "%" << endl;
    cout << "Grade      : " << s.grade() << endl;
}

// Main function
int main() {
    loadData();

    int choice;

    do {
        cout << "\n================================\n";
        cout << "       STUDENT PORTAL\n";
        cout << "================================\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Add / Update Marks\n";
        cout << "7. Calculate Result\n";
        cout << "8. Save Records\n";
        cout << "0. Exit\n";
        cout << "================================\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        try {
            switch (choice) {
                case 1: addStudent(); break;
                case 2: displayStudents(); break;
                case 3: searchStudent(); break;
                case 4: updateStudent(); break;
                case 5: deleteStudent(); break;
                case 6: addMarks(); break;
                case 7: calculateResult(); break;
                case 8:
                    saveData();
                    cout << "Records Saved!\n";
                    break;
                case 0:
                    saveData();
                    cout << "Thank You for Using Student Portal!\n";
                    break;
                default:
                    cout << "Invalid Choice! Try Again.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }

    } while (choice != 0);

    return 0;
}