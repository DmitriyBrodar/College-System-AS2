#include "Academic.h"
#include <iostream>

using namespace std;

// Constructor for the Academic class. It initializes the class using the Employee base class constructor
// and sets the specific properties related to academics.
Academic::Academic(const string& name, const string& address, const string& DOB, const string& telNumber,
               const string& ppsNumber, int grade, int numExamPapers, int leaveDays)
    : Employee(name, address, DOB, telNumber, ppsNumber, calculateInitialSalary(grade)),
      numExamPapers(numExamPapers), grade(grade), leaveDays(leaveDays) {}

// Prints the details specific to the Academic employee, adding to the general employee details.
void Academic::printDetails() const {
    cout << "\n========================== Academic ==========================\n";
    Employee::printDetails();
    cout << "Grade: \t\t\t" << grade  << "\nNumber of Exam Papers:\t" << numExamPapers << "\nLeave Days: \t\t" << leaveDays << endl;
}

// Calculates initial salary based on the academic grade.
double Academic::calculateInitialSalary(int grade) const {
    switch (grade) {
        case 1: return 30000;
        case 2: return 40000;
        case 3: return 45000;
        default: return 0;
    }
}

// Calculates the final pay by considering the number of exam papers corrected, number of leave days,
// and applying necessary deductions for taxes and PRSI
double Academic::calculatePay() const {
    double extraPayForPapers = numExamPapers * 5.0;
    double salary = getGrossPay();
    double leaveDeduction = leaveDays * 40;

    // Adjust salary for extra pay and leave deductions
    double adjustedSalary = salary + extraPayForPapers - leaveDeduction;

    // Calculate taxes and PRSI based on the adjusted salary
    double tax = adjustedSalary * TAX_RATE;
    double prsi = adjustedSalary * PRSI_RATE;

    // Final salary after all deductions
    return adjustedSalary - tax - prsi;
}

// Getter methods for class-specific properties
int Academic::getNumExamPapers() const {
    return numExamPapers;
}

int Academic::getGrade() const {
    return grade;
}

int Academic::getLeaveDays() const {
    return leaveDays;
}

// Setter methods with validation
void Academic::setNumExamPapers(int numExamPapers) {
    if (numExamPapers >= 0) {
        this->numExamPapers = numExamPapers;
    } else {
        cout << "Number of exam papers cannot be negative." << endl;
    }
}

void Academic::setGrade(int grade) {
    this->grade = grade;
    setGrossPay(calculateInitialSalary(grade)); // Recalculate gross pay when grade is updated
}

void Academic::setLeaveDays(int leaveDays) {
    if (leaveDays >= 0) {
        this->leaveDays = leaveDays;
    } else {
        cout << "Leave days cannot be negative." << endl;
    }
}
