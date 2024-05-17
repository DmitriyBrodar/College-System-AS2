#include "Clerical.h"
#include <iostream>
#include <regex>

using namespace std;

// Constructor that initializes the Clerical object using the Employee base class constructor
Clerical::Clerical(const string& name, const string& address, const string& DOB, const string& telNumber,
                    const string& ppsNumber, const string& jobTitle, int grade)
    : Employee(name, address, DOB, telNumber, ppsNumber, 0) {
    setJobTitle(jobTitle);
    setGrade(grade);
}


// Print the detailed information about the clerical staff, including job title and grade
void Clerical::printDetails() const {
    cout << "\n========================== Clerical ==========================\n";
    cout << "Job Title: \t\t" << jobTitle << endl;
    Employee::printDetails();
    cout << "Grade: \t\t\t" << grade << "\nGross Pay: \t\t" << grossPay << endl;
}

// Calculate the net pay for the clerical staff after deductions for tax and PRSI
double Clerical::calculatePay() const{
    double tax = getGrossPay() * TAX_RATE;
    double prsi = getGrossPay() * PRSI_RATE;
    return getGrossPay() - tax - prsi;
}

// Getter for job title
string Clerical::getJobTitle() const {
    return jobTitle;
}

// Getter for grade
int Clerical::getGrade() const {
    return grade;
}

// Set the job title after validating it to ensure it is a single word
void Clerical::setJobTitle(const string& jobTitle) {
    if (validateJobTitle(jobTitle)) {
        this->jobTitle = jobTitle;
    } else {
        throw invalid_argument("Invalid Job Title. Please try again.");
    }
}

// Set the clerical grade and adjust the salary based on the grade
void Clerical::setGrade(int grade) {
    double salary = salaryForGrade(grade);
    if (salary != 0) {
        this->grade = grade;
        setGrossPay(salary);
    } else {
        throw std::invalid_argument("Invalid grade for clerical staff.");
    }
}

// Determines the salary for a given grade
double Clerical::salaryForGrade(int grade) const {
    switch (grade) {
        case 1:
            return 20000;
        case 2:
            return 24000;
        default:
            return 0;
    }
}

// Validation by single word
bool Clerical::validateJobTitle(const string& title) {
    regex codePattern("^[A-Za-z]+$");
    return regex_match(title, codePattern);
}
