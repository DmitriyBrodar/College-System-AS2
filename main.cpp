/*
    Author: Dmytro Brodar
    Data: 26/04/2024

    This program is designed to store and manage college information for students and employees.
    It allows users to perform various actions such as adding, modifying and deleting records
    of students and different types of employees. Also, the program can calculate the salary
    of employees and print detailed information about students or employees.
*/
#include <iostream>
#include <string>
#include <memory>
#include <iomanip>
#include "Menu.h"
#include "StudentManager.h"
#include "EmployeeManager.h"
#include "Clerical.h"
#include "Academic.h"

using namespace std;

int main() {
    try {
        // Initialize managers for handling student and employee data
        StudentManager studentManager;
        EmployeeManager employeeManager;

        Menu menu;  // Menu object to display options
        int choice; // Variable to store user choice
        bool running = true; // Flag to control the main program loop

        // Main loop to handle user menu selections
        while (running) {
            menu.displayMenu();  // Display the menu options
            choice = menu.getUserChoice(); // Get user's choice

            switch (choice) {
                case 1: {  // Add student
                    studentManager.addStudentInterface();
                    break;
                }
                case 2: {  // Add employee
                    employeeManager.addEmployeeInterface();
                    break;
                }
                case 3: {  // Delete a record
                    string id;
                    int type;
                    bool validInput = false;
                    cout << "-------------------Delete Record-------------------" << endl;
                    while (!validInput) {
                        cout << "Choose type to delete 1. Student 2. Employee 0. Exit Enter your choose: ";
                        cin >> type;
                        cin.ignore();

                        if (type == 0) {
                            cout << "Exiting delete operation." << endl;
                            break;
                        } else if (type == 1) {
                            cout << "Enter Student ID to delete (or enter 0 to exit): ";
                            getline(cin, id);
                            if(id == "0") {
                                cout << "Exiting delete operation." << endl;
                                break;
                            }
                            studentManager.deleteStudent(id);
                            validInput = true;
                            cout << "----------Student successfully deleted.----------";
                        } else if (type == 2) {
                            cout << "Enter Employee PPSN to delete (or enter 0 to exit): ";
                            getline(cin, id);
                            if (id == "0") {
                                cout << "Exiting delete operation." << endl;
                                break;
                            }
                            employeeManager.deleteEmployee(id);
                            validInput = true;
                            cout << "----------Employee successfully deleted.----------";
                        } else {
                            cout << "Invalid type selected. Please try again or enter 0 to exit." << endl;
                        }
                    }
                    break;
                }
                case 4: {  // Modify a record
                    string id;
                    int type;
                    bool validInput = false;
                    cout << "\n-------------------Modify Record-------------------" << endl;
                    while (!validInput) {
                        cout << "Choose type to modify \n1. Student \n2. Employee \n0. Exit \nEnter your choose: ";
                        cin >> type;
                        cin.ignore();

                        if (type == 0) {
                            cout << "Exiting modify operation.\n" << endl;
                            break;
                        } else if (type == 1) {
                            cout << "Enter Student ID to modify (or enter 0 to exit): ";
                            getline(cin, id);
                            if(id == "0") {
                                cout << "Exiting modify operation.\n" << endl;
                                break;
                            }
                            studentManager.modifyStudent(id);
                            validInput = true;
                            cout << "----------Student successfully modified.----------\n\n";
                        } else if (type == 2) {
                            cout << "Enter Employee PPSN to modify (or enter 0 to exit): ";
                            getline(cin, id);
                            if (id == "0") {
                                cout << "Exiting modify operation.\n" << endl;
                                break;
                            }
                            employeeManager.modifyEmployee(id);
                            validInput = true;
                            cout << "----------Employee successfully modified.----------\n\n";
                        } else {
                            cout << "Invalid type selected. Please try again or enter 0 to exit." << endl;
                        }
                    }
                    break;
                }
                case 5: {  // Calculate salary
                    cout << "\n-------------------Calculate salary-------------------" << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    string ppsNumber;
                    bool validInput = false;

                    while (!validInput) {
                        cout << "Enter PPS number of the employee: ";
                        getline(cin, ppsNumber);

                        if (ppsNumber == "0") {
                            cout << "Exiting salary calculation operation.\n" << endl;
                            break;
                        }

                        if (!Employee::validatePPSNumber(ppsNumber)) {
                            cout << "Invalid PPS Number format. Please try again or enter 0 to exit.\n";
                        } else {
                            Employee* employee = employeeManager.findEmployee(ppsNumber);
                            if (employee) {
                                validInput = true;
                                double salary = employee->calculatePay();
                                cout << "\n====================== Pay Slip ======================\n";
                                cout << "PPS Number: \t\t" << employee->getPpsNumber() << "\n";
                                cout << "Name: \t\t\t" << employee->getName() << "\n";
                                cout << "Address: \t\t" << employee->getAddress() << "\n";
                                cout << "Date of Birth: \t\t" << employee->getDOB() << "\n";
                                cout << "Telephone: \t\t" << employee->getTelNumber() << "\n";
                                auto spt = dynamic_cast<PartTimeStudentAcademic*>(employee);
                                if (spt) {
                                    cout << "Tax Rate: \t\t0%\n";
                                    cout << "PRSI Rate: \t\t0%\n";
                                    cout << "Hours Worked: \t\t" << spt->getHoursWorked() << "\n";
                                    cout << "Hourly Rate: \t\t" << spt->getHourlyRate() << "\n";
                                    cout << "Gross Pay: \t\t" << employee->getGrossPay() << "\n";
                                    cout << "Net Pay: \t\t" << salary << "\n";
                                    cout << "Role: \t\t\tStudent and Part-time Employee\n";
                                } else {
                                    cout << "Tax Rate: \t\t" << employee->getTaxRate() * 100 << "%\n";
                                    cout << "PRSI Rate: \t\t" << employee->getPRSI() * 100 << "%\n";
                                    if (dynamic_cast<Clerical*>(employee)) {
                                        cout << "Gross Pay: \t\t" << employee->getGrossPay() << "\n";
                                        cout << "Net Pay: \t\t" << salary << "\n";
                                        cout << "Role: \t\t\tClerical\n";
                                    }
                                    if (auto acad = dynamic_cast<Academic*>(employee)) {
                                        cout << "Exam Scripts Rate: \t5\n";
                                        cout << "Number of Exam Papers:\t" << acad->getNumExamPapers() << "\n";
                                        cout << "Leave Days: \t\t" << acad->getLeaveDays() << "\n";
                                        cout << "Gross Pay: \t\t" << employee->getGrossPay() << "\n";
                                        cout << "Net Pay: \t\t" << salary << "\n";
                                        cout << "Role: \t\t\tAcademic\n";
                                    }
                                    if (auto pt = dynamic_cast<PartTimeAcademic*>(employee)) {
                                        cout << "Hours Worked: \t\t" << pt->getHoursWorked() << "\n";
                                        cout << "Hourly Rate: \t\t" << pt->getHourlyRate() << "\n";
                                        cout << "Exam Scripts Rate: \t5\n";
                                        cout << "Number of Exam Papers:\t" << pt->getNumExamPapersPT() << "\n";
                                        if (pt->getIsAlsoStudent()) {
                                            cout << "Gross Pay: \t\t" << employee->getGrossPay() * 1.03 + pt->getNumExamPapersPT() * 5<< "\n";
                                            cout << "Net Pay: \t\t" << salary << "\n";
                                            cout << "Hourly pay increase by  3%\n";
                                            cout << "Role: \t\t\tPart-time Employee and Student\n";
                                        } else {
                                            cout << "Gross Pay: \t\t" << employee->getGrossPay() + pt->getNumExamPapersPT() * 5<< "\n";
                                            cout << "Net Pay: \t\t" << salary << "\n";
                                            cout << "Role: \t\t\tPart-time Employee\n";
                                        }
                                    }
                                }
                                cout << "=======================================================\n\n";
                            } else {
                                cout << "No employee found with the PPS number provided." << endl;
                            }
                        }
                    }
                    break;
                }
                case 6: {  // Print information
                    cout << "----------Print information----------\n\n";
                    int type;
                    string id;
                    bool validInput = false;
                    while (!validInput) {
                        cout << "Choose type to print information:\n1. Student\n2. Employee\n0. Exit\nEnter your choice: ";
                        cin >> type;
                        cin.ignore();

                        if(type == 0) {
                            cout << "Exiting print information operation.\n" << endl;
                            break;
                        } else if (type == 1) {
                            cout << "Enter Student ID to print information (or enter 0 to exit): ";
                            getline(cin, id);
                            if (id == "0") {
                                cout << "Exiting print information operation.\n" << endl;
                                break;
                            }
                            cout << "\n========== Student information ==========\n";
                            studentManager.printStudentDetails(id);
                            cout << "==========================================\n\n";
                            validInput = true;
                        } else if (type == 2) {
                            cout << "Enter Employee PPSN to print information (or enter 0 to exit): ";
                            getline(cin, id);
                            if (id == "0") {
                                cout << "Exiting print information operation.\n" << endl;
                                break;
                            }
                            cout << "\n===================== Employee information ===================";
                            employeeManager.printEmployeeDetails(id);
                            cout << "==============================================================\n\n";
                            validInput = true;
                        } else {
                            cout << "Invalid type selected. Please try again or enter 0 to exit.\n";
                        }
                    }
                    break;
                }
                case 7:  // Exit the program
                    running = false;
                    cout << "----------Exiting the program----------" << endl;
                    break;
                default:
                    cout << "Invalid option, please try again." << endl;
            }
        }
    } catch (const exception& e) {
            cout << "Caught an exception: " << e.what() << endl;
        return 3; // Indicate that an error occurred
    }

    return 0;
}
