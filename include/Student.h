#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <regex>

using namespace std;

// The Student class inherits from Person and adds specific attributes related to students.
class Student : public Person {
private:
    string studentID;
    string courseCode;
    int year;
    int stream;


public:
    // Constructor to initialize a Student object with personal and academic details
    Student(const string& name, const string& address, const string& DOB, const string& telNumber,
            const string& studentID, const string& courseCode, int year, int stream);
    void printDetails() const;

    // Getters for accessing private attributes
    string getStudentID() const;
    string getCourseCode() const;
    int getYear() const;
    int getStream() const;

    // Setters for updating student attributes with validation
    void setStudentID(const string& studentID);
    void setCourseCode(const string& courseCode);
    void setYear(int year);
    void setStream(int stream);

    // Static validation methods used to check the format and correctness of input values
    static bool validateStudentID(const string& id) ;
    static bool validateCourseCode(const string& code) ;
    static bool validateYear(int year) ;
    static bool validateStream(int stream) ;
};

#endif // STUDENT_H
