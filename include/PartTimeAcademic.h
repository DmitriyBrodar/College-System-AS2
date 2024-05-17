#ifndef PARTTIMEACADEMIC_H
#define PARTTIMEACADEMIC_H

#include "Employee.h"
#include <string>

// PartTimeAcademic class inherits from Employee
// This class represents a part-time academic staff member
class PartTimeAcademic : public Employee {
protected:
    int numExamPapersPT;
    int hoursWorked;
    bool isAlsoStudent;
    static constexpr double HOURLY_RATE = 20.75;  // Hourly rate for part-time workers


public:
    // Constructor to initialize a PartTimeAcademic with personal and work details
    PartTimeAcademic(const string& name, const string& address, const string& DOB, const string& telNumber,
                     const string& ppsNumber, int hoursWorked, int numExamPapersPT = 0, bool isAlsoStudent = false);

    void printDetails()const;
    double calculatePay()const;
    EmployeeType getType() const;

    // Getters
    int getHoursWorked()const;
    int getNumExamPapersPT() const;
    bool getIsAlsoStudent() const { return isAlsoStudent; }
    double getHourlyRate() const { return HOURLY_RATE; }

    // Setters
    void setHoursWorked(int hoursWorked);
    void setNumExamPapersPT(int numExamPapersPT);
    void setIsAlsoStudent(bool isAlsoStudent);
};

#endif

