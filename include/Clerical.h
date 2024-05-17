#ifndef CLERICAL_H
#define CLERICAL_H

#include "Employee.h"
using namespace std;

// The Clerical class is derived from the Employee class and represents clerical staff within the organization.
class Clerical : public Employee {
private:
    string jobTitle;
    int grade;
    double salaryForGrade(int grade) const;

public:
    // Constructor to initialize a Clerical object with required attributes.
    Clerical(const string& name, const string& address, const string& DOB, const string& telNumber,
             const string& ppsNumber, const string& jobTitle, int grade);

    void printDetails() const;
    double calculatePay() const;

    // Getters
    string getJobTitle() const;
    int getGrade() const;
    EmployeeType getType() const override { return EmployeeType::Clerical; }
    // Setters
    void setJobTitle(const string& jobTitle);
    void setGrade(int grade);
    static bool validateJobTitle(const string& title);
};

#endif // CLERICAL_H
