#include "Student.h"
#include <iostream>
#include <regex>

using namespace std;

// Constructor that initializes a student using the provided details and calls the Person constructor
Student::Student(const string& name, const string& address, const string& DOB, const string& telNumber,
               const string& studentID, const string& courseCode, int year, int stream)
    : Person(name, address, DOB, telNumber) {
    setStudentID(studentID);
    setCourseCode(courseCode);
    setYear(year);
    setStream(stream);
}

// Prints all details of a student including those inherited from the Person class
void Student::printDetails() const{
    cout << "Student ID: \t\t" << studentID << endl;
    Person::printDetails();
    cout << "Course Code: \t\t" << courseCode << "\nYear: \t\t\t" << year << "\nStream: \t\t" << stream << endl;
}

// Validates the student ID format: must be 7 digits followed by a letter
bool Student::validateStudentID(const string& id)  {
    regex idPattern(R"(\d{7}[A-Za-z])");
    return regex_match(id, idPattern);
}

// Validates the course code format: must be exactly 2 letters
bool Student::validateCourseCode(const string& code)  {
    regex codePattern(R"([A-Za-z]{2})");
    return regex_match(code, codePattern);
}

// Validates the year: must be between 1 and 4
bool Student::validateYear(int year)  {
    return year >= 1 && year <= 4;
}

// Validates the stream: must be between 1 and 3
bool Student::validateStream(int stream)  {
    return stream >= 1 && stream <= 3;
}

// Returns the student ID
string Student::getStudentID() const {
    return studentID;
}

// Returns the course code
string Student::getCourseCode() const {
    return courseCode;
}

// Returns the current year of the student
int Student::getYear() const {
    return year;
}

// Returns the stream number of the student
int Student::getStream() const {
    return stream;
}

// Sets the student ID after validating it, throws an error if invalid
void Student::setStudentID(const string& studentID) {
    if (validateStudentID(studentID)) {
        this->studentID = studentID;
    } else {
        throw invalid_argument("Invalid Student ID. Please try again.");
    }
}

// Sets the course code after validating it, throws an error if invalid
void Student::setCourseCode(const string& courseCode) {
    if (validateCourseCode(courseCode)) {
        this->courseCode = courseCode;
    } else {
        throw invalid_argument("Invalid Course Code. Please try again.");
    }
}

// Sets the year after validating it, throws an error if invalid
void Student::setYear(int year) {
    if (validateYear(year)) {
        this->year = year;
    } else {
        throw invalid_argument("Invalid Year. Please try again.");
    }
}

// Sets the stream after validating it, throws an error if invalid
void Student::setStream(int stream) {
    if (validateStream(stream)) {
        this->stream = stream;
    } else {
        throw invalid_argument("Invalid Stream. Please try again.");
    }
}
