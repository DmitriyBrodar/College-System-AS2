#include "PartTimeStudentAcademic.h"
#include <iostream>

using namespace std;

// Constructor for PartTimeStudentAcademic class, initializes from PartTimeAcademic class
PartTimeStudentAcademic::PartTimeStudentAcademic(const string& name, const string& address, const string& DOB,
                                                 const string& telNumber, const string& studentNumber, int hoursWorked)
    : PartTimeAcademic(name, address, DOB, telNumber, studentNumber, hoursWorked, true) {
}

// Print the detailed information of the part-time student academic
void PartTimeStudentAcademic::printDetails() const {
    cout << "\n================= Student part-time employee =================\n";
    Employee::printDetails();
    cout << "Hours Worked: \t\t" << hoursWorked << "\nHourly Rate: \t\t" << HOURLY_RATE;
    cout << "\nDetails: (Student who is also a part-time employee and untaxed)" << endl;
}

// Calculate the pay for the part-time student academic
double PartTimeStudentAcademic::calculatePay() const {
    return hoursWorked * HOURLY_RATE;
}
