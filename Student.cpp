#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    int id;
    string name;
    string course;
    float m1, m2, m3;

    // Constructor
    Student(int i, string n, string c,
            float a, float b, float d) {
        id = i;
        name = n;
        course = c;
        m1 = a;
        m2 = b;
        m3 = d;
    }

    // Calculate Total
    float total() {
        return m1 + m2 + m3;
    }

    // Calculate Percentage
    float percentage() {
        return total() / 3;
    }

    // Calculate Grade
    string grade() {
        float p = percentage();

        if (p >= 90)
            return "A+";
        else if (p >= 80)
            return "A";
        else if (p >= 70)
            return "B";
        else if (p >= 60)
            return "C";
        else if (p >= 40)
            return "D";
        else
            return "Fail";
    }

    // Display Student Details
    void display() {
        cout << "\nStudent ID: " << id;
        cout << "\nStudent Name: " << name;
        cout << "\nCourse: " << course;
        cout << "\nTotal Marks: " << total();
        cout << "\nPercentage: " << percentage() << "%";
        cout << "\nGrade: " << grade();
        cout << "\n";
    }
};