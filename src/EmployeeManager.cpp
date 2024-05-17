#include "EmployeeManager.h"
#include "Clerical.h"
#include "Academic.h"
#include "PartTimeAcademic.h"
#include "PartTimeStudentAcademic.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

// Constructor: loads employees from a file when an EmployeeManager object is instantiated.
EmployeeManager::EmployeeManager() {
    loadEmployees();
}

// Loads employee data from a file and creates appropriate employee objects.
void EmployeeManager::loadEmployees() {
    ifstream file("employees.txt");
    if (!file.is_open()) {
        cerr << "Failed to open employees.txt for reading." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type, name, address, DOB, telNumber, ppsNumber;
        getline(ss, type, ',');
        getline(ss, ppsNumber, ',');
        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, DOB, ',');
        getline(ss, telNumber, ',');

        if (type == "Clerical") {
            string jobTitle;
            int grade;
            getline(ss, jobTitle, ',');
            ss >> grade;
            employees.push_back(make_unique<Clerical>(name, address, DOB, telNumber, ppsNumber, jobTitle, grade));
        } else if (type == "Academic") {
            int grade, numExamPapers, leaveDays;
            ss >> grade;
            ss.ignore(); // Ignore the comma
            ss >> numExamPapers;
            ss.ignore(); // Ignore the comma
            ss >> leaveDays;
            employees.push_back(make_unique<Academic>(name, address, DOB, telNumber, ppsNumber, grade, numExamPapers, leaveDays));
        } else if (type == "Part-Time Academic") {
            int hoursWorked, numExamPapersPT;
            bool isAlsoStudent;
            ss >> hoursWorked;
            ss.ignore(); // Ignore the comma
            ss >> numExamPapersPT;
            ss.ignore(); // Ignore the comma
            ss >> isAlsoStudent;
            employees.push_back(make_unique<PartTimeAcademic>(name, address, DOB, telNumber, ppsNumber, hoursWorked, numExamPapersPT, isAlsoStudent));
        } else if (type == "Student Part-Time") {
            int hoursWorked;
            ss >> hoursWorked;
            employees.push_back(make_unique<PartTimeStudentAcademic>(name, address, DOB, telNumber, ppsNumber, hoursWorked));
        }
    }
    file.close();
}

// Checks if an employee with the given PPS number exists.
bool EmployeeManager::isPPSNumberExist(const string& ppsNumber) {
    return findEmployee(ppsNumber) != nullptr;
}

// Interface to add a new employee to the system.
void EmployeeManager::addEmployeeInterface() {
    if (employees.size() >= 15) {
        cout << "The maximum number of employees has been reached.\n";
        return;
    }

    string name, address, DOB, telNumber, ppsNumber;
    int type, hoursWorked, grade, numExamPapers, numExamPapersPT, leaveDays;
    bool isAlsoStudent;
    cout << "\n-------------------Add Employee Record-------------------";
    // Input for employee type.
    cout << "\nEnter employee type: \n1. Clerical \n2. Academic \n3. Part-Time Academic \n4. Student wanting to be Part-Time Employee \nMake a choice: ";
    cin >> type;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

    // Validation for employee type selection.
    if (type < 1 || type > 4) {
        cout << "Invalid employee type selected.\n";
        return;
    }

    // Input for PPSN
    while (true) {
        cout << "\nEnter PPS number or Student ID (7 digits followed by a letter): ";
        getline(cin, ppsNumber);

        if (ppsNumber.empty()) {
            cout << "PPSN cannot be empty. Please enter a valid date.\n";
            continue;
        }
        if (!Employee::validatePPSNumber(ppsNumber)) {
            cout << "Invalid PPS Number. Please try again.\n";
        } else if (isPPSNumberExist(ppsNumber)) {
            cout << "PPS Number already exists. Please try again.\n";
        } else {
            break;
        }
    }

    // Input for employee name
    cout << "Enter name: ";
    getline(cin, name);

    // Input for employee address
    cout << "Enter address: ";
    getline(cin, address);

    // Input and validation for date of birth
    while (true) {
        cout << "Enter date of birth (dd/mm/yyyy): ";
        getline(cin, DOB);
        if (DOB.empty()) {
            cout << "Date of birth cannot be empty. Please enter a valid date.\n";
            continue;  // Continue prompting if input is empty
        }
        if (!Person::validateDOB(DOB)) {
            cout << "Error: Invalid date format. Expected 'dd/mm/yyyy'. Please try again.\n";
        } else {
            break;  // Break the loop if the date format is correct
        }
    }

    // Input and validation for telephone number
    do {
        cout << "Enter telephone number (0XX-XXXXXXX): ";
        getline(cin, telNumber);
        if (!Person::validateTelNumber(telNumber)) {
            cout << "Error: Invalid telephone number format. Please try again.\n";
        } else {
            break;
        }
    } while (true);

    // Handling specific employee type fields.
    switch (type) {
    case 1:{ // Clerical
        string jobTitle;
        do {
            cout << "Enter job title: ";
            getline(cin, jobTitle);  // Read the full input line for job title
            if (!Clerical::validateJobTitle(jobTitle)) {
                cout << "Error: Invalid Job Title. Expected a single word. Please try again.\n";
                cin.clear();
            } else {
                break;
            }
        } while (true);


        cout << "Enter grade (1 or 2): ";
        while(!(cin >> grade) || (grade != 1 && grade != 2)) { // Validation for grade
            cout << "Error: Invalid grade. Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer after reading grade
        employees.push_back(make_unique<Clerical>(name, address, DOB, telNumber, ppsNumber, jobTitle, grade));
        break;
    }
    case 2: { // Academic
        cout << "Enter grade (1, 2, or 3): ";
        while(!(cin >> grade) || (grade != 1 && grade != 2 && grade != 3)) { // Validation for grade
            cout << "Error: Invalid grade. Please enter 1, 2 or 3.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter number of exam papers corrected this month: ";
        cin >> numExamPapers;
        cout << "Enter number of leave days this month: ";
        cin >> leaveDays;
        employees.push_back(make_unique<Academic>(name, address, DOB, telNumber, ppsNumber, grade, numExamPapers, leaveDays));
        break;
    }
    case 3:{ // Part-Time Academic
        cout << "Enter hours worked: ";
        cin >> hoursWorked;
        cout << "Enter number of exam papers corrected this month: ";
        cin >> numExamPapersPT;
        cout << "Is also a student? (1 = Yes, 0 = No): ";

        while(!(cin >> isAlsoStudent) || (isAlsoStudent != 0 && isAlsoStudent != 1)) { // Validation for grade
            cout << "Error: Invalid input. Please enter 0 or 1.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        employees.push_back(make_unique<PartTimeAcademic>(name, address, DOB, telNumber, ppsNumber, hoursWorked, numExamPapersPT, isAlsoStudent));
        break;
    }
    case 4:{ // Student wanting to be Part-Time Employee
        cout << "Enter hours worked: ";
        cin >> hoursWorked;
        employees.push_back(make_unique<PartTimeStudentAcademic>(name, address, DOB, telNumber, ppsNumber, hoursWorked));
        break;
    }
    }

    saveEmployees(); // Save the employee details
    cout << "----------Employee successfully added and saved.----------\n\n";
}

// Saves employee data to a file.
void EmployeeManager::saveEmployees() const {
    ofstream file("employees.txt");
    if (!file.is_open()) {
        cout << "Failed to open the file for saving." << endl;
        return;
    }

    for (const auto& employee : employees) {
        if (auto cler = dynamic_cast<Clerical*>(employee.get())) {
            file << "Clerical," << cler->getPpsNumber() << ","
                 << cler->getName() << ","
                 << cler->getAddress() << ","
                 << cler->getDOB() << ","
                 << cler->getTelNumber() << ","
                 << cler->getJobTitle() << ","
                 << cler->getGrade() << "\n";
        } else if (auto acad = dynamic_cast<Academic*>(employee.get())) {
            file << "Academic," << acad->getPpsNumber() << ","
                 << acad->getName() << ","
                 << acad->getAddress() << ","
                 << acad->getDOB() << ","
                 << acad->getTelNumber() << ","
                 << acad->getGrade() << ","
                 << acad->getNumExamPapers() << ","
                 << acad->getLeaveDays() << "\n";
        } else if (auto partTime = dynamic_cast<PartTimeAcademic*>(employee.get())) {
            if (auto partTimeStudent = dynamic_cast<PartTimeStudentAcademic*>(partTime)) {
                file << "Student Part-Time," << partTimeStudent->getPpsNumber() << ","
                     << partTimeStudent->getName() << ","
                     << partTimeStudent->getAddress() << ","
                     << partTimeStudent->getDOB() << ","
                     << partTimeStudent->getTelNumber() << ","
                     << partTimeStudent->getHoursWorked() << "\n";
            } else {
                file << "Part-Time Academic," << partTime->getPpsNumber() << ","
                     << partTime->getName() << ","
                     << partTime->getAddress() << ","
                     << partTime->getDOB() << ","
                     << partTime->getTelNumber() << ","
                     << partTime->getHoursWorked() << ","
                     << partTime->getNumExamPapersPT() << ","
                     << (partTime->getIsAlsoStudent() ? "1" : "0") << "\n";
            }
        }
    }

    file.close();
    cout << "Data successfully saved to the file." << endl;
}

// Deletes an employee based on the PPS number.
void EmployeeManager::deleteEmployee(const string& ppsNumber) {
    auto it = remove_if(employees.begin(), employees.end(),
                        [&ppsNumber](const unique_ptr<Employee>& emp) { return emp->getPpsNumber() == ppsNumber; });

    if (it != employees.end()) {
        employees.erase(it, employees.end());
        cout << "Employee deleted successfully.\n";
        saveEmployees();  // Save changes to the file immediately after deleting.
    } else {
        cout << "Employee not found.\n";
    }
}

// Modifies the details of an existing employee.
void EmployeeManager::modifyEmployee(const string& ppsNumber) {
    auto it = find_if(employees.begin(), employees.end(),
                      [&](const unique_ptr<Employee>& emp) { return emp->getPpsNumber() == ppsNumber; });
    if (it == employees.end()) {
        cout << "Employee not found!\n";
        return;
    }

    Employee* emp = it->get();
    string input;
    int numInput;
    bool boolInput;

    cout << "Modifying employee details. Press enter to skip any field.\n";

    // Modify employee name
    cout << "Current name: " << emp->getName() << "\nEnter new name (or enter to skip): ";
    getline(cin, input);
    if (!input.empty()) emp->setName(input);

    // Modify address
    cout << "Current address: " << emp->getAddress() << "\nEnter new address (or enter to skip): ";
    getline(cin, input);
    if (!input.empty()) emp->setAddress(input);

    // Modify date of birth with validation
    while (true) {
        cout << "Current date of birth: " << emp->getDOB() << "\nEnter new date of birth (dd/mm/yyyy, or enter to skip): ";
        getline(cin, input);
        if (input.empty()) break;
        if (!Person::validateDOB(input)) {
            cout << "Error: Invalid date format. Expected 'dd/mm/yyyy'. Please try again.\n";
        } else {
            emp->setDOB(input);
            break;
        }
    }

    // Modify telephone number with validation
    while (true) {
        cout << "Current telephone number: " << emp->getTelNumber() << "\nEnter new telephone number (0XX-XXXXXXX, or enter to skip): ";
        getline(cin, input);
        if (input.empty()) break;
        if (!Person::validateTelNumber(input)) {
            cout << "Error: Invalid telephone number format. Please try again.\n";
        } else {
            emp->setTelNumber(input);
            break;
        }
    }

    // Modify specific fields based on employee type
    if (auto cler = dynamic_cast<Clerical*>(emp)) {
        // Modify job title with validation
        do {
            cout << "Current job title: " << cler->getJobTitle() << "\nEnter new job title (or enter to skip): ";
            getline(cin, input);
            if (input.empty()) break;
            if (!Clerical::validateJobTitle(input)) {
                cout << "Error: Invalid job title. Expected a single word. Please try again.\n";
            } else {
                cler->setJobTitle(input);
                break;
            }
        } while (true);

        // Modify grade
        cout << "Current grade: " << cler->getGrade() << "\nEnter new grade (1 or 2, or enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            stringstream(input) >> numInput;
            if (numInput == 1 || numInput == 2) {
                cler->setGrade(numInput);
            } else {
                cout << "Error: Invalid grade. Please enter 1 or 2.\n";
            }
        }
    } else if (auto acad = dynamic_cast<Academic*>(emp)) {
        // Modify number of exam papers
        cout << "Current number of exam papers: " << acad->getNumExamPapers() << "\nEnter new number of exam papers (or enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            stringstream(input) >> numInput;
            acad->setNumExamPapers(numInput);
        }

        // Modify leave days
        cout << "Current leave days: " << acad->getLeaveDays() << "\nEnter new leave days (or enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            stringstream(input) >> numInput;
            acad->setLeaveDays(numInput);
        }
    } else if (auto partTime = dynamic_cast<PartTimeAcademic*>(emp)) {
        // Modify hours worked
        cout << "Current hours worked: " << partTime->getHoursWorked() << "\nEnter new hours worked (or enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            stringstream(input) >> numInput;
            if (numInput >= 0) {
                partTime->setHoursWorked(numInput);
            } else {
                cout << "Error: Hours worked cannot be negative.\n";
            }
        }

        // Modify number of exam papers
        cout << "Current number of exam papers: " << partTime->getNumExamPapersPT() << "\nEnter new number of exam papers (or enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            stringstream(input) >> numInput;
            partTime->setNumExamPapersPT(numInput);
        }

        // Modify isAlsoStudent
        cout << "Is also a student? (current: " << (partTime->getIsAlsoStudent() ? "Yes" : "No") << ", enter 1 for Yes or 0 for No, or enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            stringstream(input) >> boolInput;
            partTime->setIsAlsoStudent(boolInput);
        }
    } else if (auto partTimeStudent = dynamic_cast<PartTimeStudentAcademic*>(emp)) {

        // PartTimeStudentAcademic specific modifications
        cout << "Current hours worked: " << partTimeStudent->getHoursWorked() << "\nEnter new hours worked (or enter to skip): ";
        getline(cin, input);
        if (!input.empty()) {
            stringstream(input) >> numInput;
            if (numInput >= 0) {
                partTimeStudent->setHoursWorked(numInput);
            } else {
                cout << "Error: Hours worked cannot be negative.\n";
            }
        }
    }

    saveEmployees();
    cout << "Employee details updated successfully.\n";
}

// Prints the details of an employee based on their PPS number.
void EmployeeManager::printEmployeeDetails(const string& ppsNumber) const {
    const Employee* emp = findEmployee(ppsNumber);
    if (emp) {
        emp->printDetails();
    } else {
        cout << "\nEmployee not found!" << endl;
    }
}

// Finds an employee by their PPS number and returns a pointer to the employee object.
Employee* EmployeeManager::findEmployee(const string& ppsNumber) const {
    for (const auto& emp : employees) {
        if (emp->getPpsNumber() == ppsNumber) {
            return emp.get(); // Return the raw pointer to the employee object.
        }
    }
    return nullptr; // Return nullptr if no employee is found with the given PPS number.
}
