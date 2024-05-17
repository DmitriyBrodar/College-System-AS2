#include <iostream>
#include "Menu.h"

using namespace std;

// Method to display the main menu of the College Information System
void Menu::displayMenu()
{
cout << "----Welcome to the College Information System!----" << endl;
cout << "\nYou can manage your data, select an option below:" << endl;
cout << "\n1. Add Student Record." << endl;
cout << "2. Add Employee Record." << endl;
cout << "3. Delete Record." << endl;
cout << "4. Modify Record." << endl;
cout << "5. Calculate Salary." << endl;
cout << "6. Print Information." << endl;
cout << "7. Exit.\n" << endl;
cout << "Please choose an option by entering the number: ";
}

// Method to get the user's menu selection
int Menu::getUserChoice()
{
    int choice;
    cin >> choice;
    return choice;
}
