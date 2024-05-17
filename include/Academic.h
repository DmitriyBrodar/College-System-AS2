#ifndef ACADEMIC_H
#define ACADEMIC_H

#include "Employee.h"

// The Academic class inherits from Employee
class Academic : public Employee {
private:
    int numExamPapers;
    int grade;
    int leaveDays;
    double calculateInitialSalary(int grade) const;  // Utility function to set initial salary based on grade

public:
    // Constructor to initialize an Academic employee with necessary details.
    Academic(const string& name, const string& address, const string& DOB, const string& telNumber,
            const string& ppsNumber,  int grade, int numExamPapers = 0, int leaveDays = 0);

    void printDetails()const ;
    double calculatePay()const ;

    // Getters for accessing private fields.
    int getNumExamPapers() const;
    int getGrade() const;
    int getLeaveDays() const;

    // Returns Academic type of Employee
    EmployeeType getType() const override { return EmployeeType::Academic; }

    // Setters for updating private fields.
    void setNumExamPapers(int numExamPapers);
    void setGrade(int grade);
    void setLeaveDays(int leaveDays);
};

#endif
