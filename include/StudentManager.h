#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "Student.h"
#include <vector>
#include <string>

using namespace std;
// The StudentManager class is responsible for managing a collection of Student objects.
// It provides functionality to load, add, save, delete, modify, and retrieve student records.
class StudentManager {
private:
    vector<Student> students; // Container to hold all student records
    void loadStudents();
    bool isStudentIDExist(const string& studentID);

public:
    // Constructor, calls loadStudents to populate the vector from file data
    StudentManager();
    void addStudentInterface();
    void saveStudents() const;
    void deleteStudent(const string& studentID);
    void modifyStudent(const string& studentID);
    void printStudentDetails(const string& studentID) const;
    const Student& findStudent(const string& studentID) const;

};

#endif // STUDENTMANAGER_H
