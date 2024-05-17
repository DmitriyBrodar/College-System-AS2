#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include "Employee.h"
#include "Clerical.h"
#include "Academic.h"
#include "PartTimeAcademic.h"
#include "PartTimeStudentAcademic.h"
#include <vector>
#include <string>
#include <memory>

using namespace std;

// The EmployeeManager class manages operations related to employees, including adding, deleting,
// and modifying employee records.
class EmployeeManager {
private:
    // A list of employees managed using smart pointers for automatic memory management.
    vector<unique_ptr<Employee>> employees;
    void loadEmployees();
    bool isPPSNumberExist(const string& ppsNumber);
public:
    EmployeeManager(); // Constructor that initializes the EmployeeManager and loads existing employees from storage.
    void saveEmployees() const;
    void addEmployeeInterface();
    void deleteEmployee(const string& ppsNumber);
    void modifyEmployee(const string& ppsNumber);
    void printEmployeeDetails(const string& ppsNumber) const;
    Employee* findEmployee(const string& ppsNumber) const;
};

#endif
