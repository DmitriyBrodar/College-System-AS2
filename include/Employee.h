#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"
#include <string>
#include <regex>
using namespace std;

// Enum class to define different types of employees.
enum class EmployeeType {
    Clerical,
    Academic,
    PartTimeAcademic,
    PartTimeStudentAcademic
};

// Overloads the ostream operator to allow direct output of EmployeeType enum values as strings.
ostream& operator <<(ostream& os, const EmployeeType& type);

// Employee class derived from Person, adding specific attributes and behaviors relevant to employees.
class Employee : public Person {
protected:
    string ppsNumber;
    double grossPay;
    static constexpr double TAX_RATE = 0.22; // 22% tax rate for all employees
    static constexpr double PRSI_RATE = 0.04; // 4% PRSI rate for all employees

public:
    // Constructor initializing the employee with personal and employment details.
    Employee(const string& name, const string& address, const string& DOB, const string& telNumber,
            const string& ppsNumber, double grossPay);

    // Override the printDetails function to ensure it matches the base class signature
    void printDetails() const;
    virtual double calculatePay() const = 0;

    // Getter functions to access private attributes.
    string getPpsNumber() const;
    double getTaxRate() const;
    double getGrossPay() const;
    double getPRSI() const;

    // Setter functions to modify private attributes.
    void setPpsNumber(const string& ppsNumber);
    void setGrossPay(double grossPay);

    virtual int getGrade() const;
    virtual EmployeeType getType() const = 0; // virtual function to return the type of employee as defined in EmployeeType.

    static bool validatePPSNumber(const string& pps);
};

#endif
