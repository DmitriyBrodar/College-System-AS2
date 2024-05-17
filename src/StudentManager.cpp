#include "StudentManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

StudentManager::StudentManager() {
    loadStudents();  // Load existing student records from file on initialization
}

void StudentManager::loadStudents() {
    ifstream file("students.txt"); // Open the students file for reading
    string line;
    while (getline(file, line)) { // Read each line representing a single student's data
        stringstream ss(line);
        string name, address, dob, telNumber, studentID, courseCode;
        int year, stream;
        char delim;

        // Extract student details from the line using commas as delimiters
        getline(ss, studentID, ',');
        getline(ss, name, ',');
        getline(ss, address, ',');
        getline(ss, dob, ',');
        getline(ss, telNumber, ',');
        getline(ss, courseCode, ',');
        ss >> year >> delim >> stream;

        // Create a new student object and add it to the list of students
        students.emplace_back(name, address, dob, telNumber, studentID, courseCode, year, stream);
    }
    file.close(); // Close the file after reading all lines
}

bool StudentManager::isStudentIDExist(const string& studentID) {
    // Check if a student ID already exists in the list of students
    for (const auto& s : students) {
        if (s.getStudentID() == studentID) {
            return true;
        }
    }
    return false;
}

void StudentManager::addStudentInterface() {
    if (students.size() >= 200) {
        cout << "The maximum number of students (200) has been reached.\n";
        return;
    }

    string name, address, dob, telNumber, studentID, courseCode;
    int year, stream;

    // Clear the input buffer to prevent reading any leftover data
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n-------------------Add Student Record-------------------";
    // Input loop for student ID with validation
    while (true) {
        cout << "\nEnter student ID (7 digits followed by a letter): ";
        getline(cin, studentID);
        if (!Student::validateStudentID(studentID)) {
            cout << "Error: Invalid Student ID format. Please try again.\n";
        } else if (isStudentIDExist(studentID)) {
            cout << "A student with this ID already exists. Please enter a different ID.\n";
        } else {
            break;
        }
    }

    // Collect and validate other student details
    cout << "Enter student name: ";
    getline(cin, name);

    cout << "Enter address: ";
    getline(cin, address);


    while (true) {
        cout << "Enter date of birth (dd/mm/yyyy): ";
        getline(cin, dob);
        if (dob.empty()) {
            cout << "Date of birth cannot be empty. Please enter a valid date.\n";
            continue;  // Continue prompting if input is empty
        }
        if (!Person::validateDOB(dob)) {
            cout << "Error: Invalid date format. Expected 'dd/mm/yyyy'. Please try again.\n";
        } else {
            break;  // Break the loop if the date format is correct
        }
    }

    do {
        cout << "Enter telephone number (0XX-XXXXXXX): ";
        getline(cin, telNumber);
        if (!Person::validateTelNumber(telNumber)) {
            cout << "Error: Invalid telephone number format. Please try again.\n";
        } else {
            break;
        }
    } while (true);

    do {
        cout << "Enter course code (2 letters): ";
        getline(cin, courseCode);
        if (!Student::validateCourseCode(courseCode)) {
            cout << "Error: Invalid Course Code format. Expected 2 letters. Please try again.\n";
        } else {
            break;
        }
    } while (true);

    do {
        cout << "Enter year (1-4): ";
        if (!(cin >> year) || !Student::validateYear(year)) {
            cout << "Error: Invalid Year. Expected a number from 1 to 4. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    do {
        cout << "Enter stream (1-3): ";
        if (!(cin >> stream) || !Student::validateStream(stream)) {
            cout << "Error: Invalid Stream. Expected a number from 1 to 3. Please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    } while (true);

    cin.ignore(); // Clear the newline character from the buffer after the last cin

    // Add the validated student to the system
    Student newStudent(name, address, dob, telNumber, studentID, courseCode, year, stream);
    students.push_back(newStudent);
    saveStudents(); // Persist the newly added student to file
    cout << "----------Student successfully added and saved.----------\n\n";
}

void StudentManager::saveStudents() const {
    ofstream file("students.txt", ios::trunc); // Open file to write all current students to it

    if (!file.is_open()) {
        cout << "Failed to open the file for saving." << endl;
        return;
    }

    for (const auto& student : students) {
        file << student.getStudentID() << ','
             << student.getName() << ','
             << student.getAddress() << ','
             << student.getDOB() << ','
             << student.getTelNumber() << ','
             << student.getCourseCode() << ','
             << student.getYear() << ','
             << student.getStream() << '\n';
    }

    file.close(); // Close the file after writing
    cout << "Data successfully saved to the file." << endl;
}

void StudentManager::deleteStudent(const string& studentID) {
    auto it = remove_if(students.begin(), students.end(),
                        [&studentID](const Student& s) { return s.getStudentID() == studentID; });
    bool found = (it != students.end());
    if (found) {
        students.erase(it, students.end());
        cout << "Student deleted successfully.\n";
        saveStudents(); // Save the updated list of students to the file
    } else {
        cout << "Student not found.\n";
    }
}

void StudentManager::modifyStudent(const string& studentID) {
    auto it = find_if(students.begin(), students.end(),
                      [&](const Student& s) { return s.getStudentID() == studentID; });
    if (it == students.end()) {
        cout << "Student not found!\n";
        return;
    }

    Student& student = *it;
    string input;
    int numInput;

    cout << "Modifying student details. Press enter to skip any field.\n";

    // Interactively modify student details, with optional skipping
    cout << "Current name: " << student.getName() << "\nEnter new name (or enter to skip): ";
    getline(cin, input);
    if (!input.empty()) student.setName(input);

    cout << "Current address: " << student.getAddress() << "\nEnter new address (or enter to skip): ";
    getline(cin, input);
    if (!input.empty()) student.setAddress(input);

    while (true) {
        cout << "Current date of birth: " << student.getDOB() << "\nEnter new date of birth (dd/mm/yyyy, or enter to skip): ";
        getline(cin, input);
        if (input.empty()) break;
        if (!Person::validateDOB(input)) {
            cout << "Error: Invalid date format. Expected 'dd/mm/yyyy'. Please try again.\n";
        } else {
            student.setDOB(input);
            break;
        }
    }

    while (true) {
        cout << "Current telephone number: " << student.getTelNumber() << "\nEnter new telephone number (0XX-XXXXXXX, or enter to skip): ";
        getline(cin, input);
        if (input.empty()) break;
        if (!Person::validateTelNumber(input)) {
            cout << "Error: Invalid telephone number format. Please try again.\n";
        } else {
            student.setTelNumber(input);
            break;
        }
    }

    while (true) {
        cout << "Current course code: " << student.getCourseCode() << "\nEnter new course code (2 letters, or enter to skip): ";
        getline(cin, input);
        if (input.empty()) break;
        if (!Student::validateCourseCode(input)) {
            cout << "Error: Invalid Course Code format. Expected 2 letters. Please try again.\n";
        } else {
            student.setCourseCode(input);
            break;
        }
    }

    while (true) {
        cout << "Current year: " << student.getYear() << "\nEnter new year (1-4, or enter to skip): ";
        getline(cin, input);
        if (input.empty()) break;
        stringstream(input) >> numInput;
        if (!Student::validateYear(numInput)) {
            cout << "Error: Invalid Year. Expected a number from 1 to 4. Please try again.\n";
        } else {
            student.setYear(numInput);
            break;
        }
    }

    while (true) {
        cout << "Current stream: " << student.getStream() << "\nEnter new stream (1-3, or enter to skip): ";
        getline(cin, input);
        if (input.empty()) break;
        stringstream(input) >> numInput;
        if (!Student::validateStream(numInput)) {
            cout << "Error: Invalid Stream. Expected a number from 1 to 3. Please try again.\n";
        } else {
            student.setStream(numInput);
            break;
        }
    }

    saveStudents(); // Persist changes to file
    cout << "Student details updated successfully.\n";
}

void StudentManager::printStudentDetails(const string& studentID) const {
    try {
        const Student& student = findStudent(studentID);
        student.printDetails();  // Use dot operator since 'student' is a reference
    } catch (const std::runtime_error& e) {
        cout << "\nError: " << e.what() << endl;  // Handle the exception if student is not found
    }
}


const Student& StudentManager::findStudent(const string& studentID) const {
    for (const auto& student : students) {
        if (student.getStudentID() == studentID) {
            return student;  // Return a reference to the student
        }
    }
    throw std::runtime_error("Student not found");  // Throw an exception if no student is found
}
