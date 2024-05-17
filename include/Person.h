#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <regex>

using namespace std;

// Person is a base class for representing basic personal information.
class Person {
protected:
    string name;
    string address;
    string DOB; // Date of Birth
    string telNumber;

public:
    // Constructor to initialize a person with name, address, date of birth, and telephone number
    Person(const string& name, const string& address, const string& DOB, const string& telNumber);
    virtual void printDetails()const;
    virtual ~Person() {};

    // Getters to access protected properties
    string getName() const;
    string getAddress() const;
    string getDOB() const;
    string getTelNumber() const;

    // Setters to modify protected properties with validation
    void setName(const string& name);
    void setAddress(const string& address);
    void setDOB(const string& DOB);
    void setTelNumber(const string& telNumber);

    // Static methods for validating DOB and telephone number formats
    static bool validateDOB(const string& dob);
    static bool validateTelNumber(const string& telNumber);
};

#endif // PERSON_H
