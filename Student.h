#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    int id;
    string name;
    string course;
    float marks;

public:

    // Constructor
    Student(int i, string n, string c, float m);

    // Getter Functions
    int getId() const;
    string getName() const;
    string getCourse() const;
    float getMarks() const;

    // Update Student Details
    void update(string n, string c);

    // Update Marks
    void setMarks(float m);

    // Calculate Percentage
    float percentage() const;

    // Calculate Grade
    string grade() const;

    // Display Student Details
    void display() const;
};

#endif