#include "Employee.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor for the Employee class, initializes from Person class and sets additional properties.
Employee::Employee(const string& name, const string& address, const string& DOB, const string& telNumber,
                    const string& ppsNumber, double grossPay)
    : Person(name, address, DOB, telNumber), grossPay(grossPay) {
    setPpsNumber(ppsNumber);
}

// Prints details of the employee, extending functionality from the Person class.
void Employee::printDetails() const {
    cout << "PPS Number: \t\t" << ppsNumber << endl;
    Person::printDetails();
}

// Returns the PPS number of the employee.
string Employee::getPpsNumber() const {
    return ppsNumber;
}

// Returns the tax rate applied to the employee.
double Employee::getTaxRate() const {
    return TAX_RATE;
}

// Returns the gross pay of the employee.
double Employee::getGrossPay() const {
    return grossPay;
}

// Returns the PRSI rate for the employee.
double Employee::getPRSI() const {
    return PRSI_RATE;
}

// Validates and sets the PPS number if the format is correct, throws an exception otherwise.
void Employee::setPpsNumber(const string& ppsNumber) {
    if (validatePPSNumber(ppsNumber)) {
        this->ppsNumber = ppsNumber;
    } else {
        throw invalid_argument("Invalid PPS Number format. Please try again.");
    }
}

// Sets the gross pay for the employee.
void Employee::setGrossPay(double grossPay) {
    this->grossPay = grossPay;
}

// Validates the format of the PPS number (7 digits followed by a letter).
bool Employee::validatePPSNumber(const string& pps) {
    regex ppsPattern(R"(\d{7}[A-Za-z])");
    return regex_match(pps, ppsPattern);
}

// Returns the grade of the employee; returns -1 by default as it may not apply to all employees.
int Employee::getGrade() const {
    return -1;
}

// Overloads the stream insertion operator to print employee types.
ostream& operator<<(ostream& os, const EmployeeType& type) {
    switch (type) {
        case EmployeeType::Clerical: os << "Clerical"; break;
        case EmployeeType::Academic: os << "Academic"; break;
        case EmployeeType::PartTimeAcademic: os << "Part-Time Academic"; break;
        case EmployeeType::PartTimeStudentAcademic: os << "Student Part-Time"; break;
    }
    return os;
}
