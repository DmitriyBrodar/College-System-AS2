#include "PartTimeAcademic.h"
#include <iostream>
#include <stdexcept>

using namespace std;

// Constructor for PartTimeAcademic, initializing with base class Employee
PartTimeAcademic::PartTimeAcademic(const string& name, const string& address, const string& DOB, const string& telNumber,
                     const string& ppsNumber, int hoursWorked, int numExamPapersPT, bool isAlsoStudent)
    : Employee(name, address, DOB, telNumber, ppsNumber, hoursWorked * HOURLY_RATE),
      hoursWorked(hoursWorked), numExamPapersPT(numExamPapersPT), isAlsoStudent(isAlsoStudent) {
}

// Method to print detailed information of the part-time academic employee
void PartTimeAcademic::printDetails() const{
    cout << "\n===================== Part-time employee =====================\n";
    Employee::printDetails();

    if (isAlsoStudent) {
        cout << "Hours Worked: \t\t" << hoursWorked << "\nNumber of Exam Papers:\t" << numExamPapersPT << "\nHourly Rate: \t\t" << HOURLY_RATE * 1.03 << "\nGross Pay: \t\t" << grossPay * 1.03 + numExamPapersPT * 5.0 << endl;
        cout << "Details: (Part-time employee who is also a student, +3% rate)\n";
    } else {
        cout << "Hours Worked: \t\t" << hoursWorked << "\nNumber of Exam Papers:\t" << numExamPapersPT << "\nHourly Rate: \t\t" << HOURLY_RATE << "\nGross Pay: \t\t" << grossPay + numExamPapersPT * 5.0<< endl;
    }
}

// Calculate and return the pay of the part-time academic, adjusting for student status
double PartTimeAcademic::calculatePay() const {
    double extraPayForPapers = numExamPapersPT * 5.0;
    double basePay = hoursWorked * HOURLY_RATE + extraPayForPapers;
    if (isAlsoStudent) {
        basePay = hoursWorked * HOURLY_RATE * 1.03 + extraPayForPapers; // Apply 3% pay increase for students
    }
    double tax = basePay * TAX_RATE;
    double prsi = basePay * PRSI_RATE;
    return basePay - tax - prsi;
}

// Method to return the type of employee, which is PartTimeAcademic
EmployeeType PartTimeAcademic::getType() const {
    return EmployeeType::PartTimeAcademic;
}

// Getter for hours worked
int PartTimeAcademic::getHoursWorked() const {
    return hoursWorked;
}

int PartTimeAcademic::getNumExamPapersPT() const {
    return numExamPapersPT;
}

// Setter for hours worked, includes a check for negative hours
void PartTimeAcademic::setHoursWorked(int hoursWorked) {
    if (hoursWorked >= 0) {
        this->hoursWorked = hoursWorked;
    } else {
        throw invalid_argument("Hours worked cannot be negative.");
    }
}

// Setter for the student status of the employee
void PartTimeAcademic::setIsAlsoStudent(bool isAlsoStudent) {
    this->isAlsoStudent = isAlsoStudent;
}

// Setter methods with validation
void PartTimeAcademic::setNumExamPapersPT(int numExamPapersPT) {
    if (numExamPapersPT >= 0) {
        this->numExamPapersPT = numExamPapersPT;
    } else {
        cout << "Number of exam papers cannot be negative." << endl;
    }
}
