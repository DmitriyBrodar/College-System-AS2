#include "Person.h"

using namespace std;

// Constructor initializes a Person object with provided name, address, date of birth, and telephone number
Person::Person(const string& name, const string& address, const string& DOB, const string& telNumber) {
    setName(name);         // Sets the name using the setName method
    setAddress(address);   // Sets the address using the setAddress method
    setDOB(DOB);           // Sets the date of birth after validation
    setTelNumber(telNumber); // Sets the telephone number after validation
}

// Print the details of the person
void Person::printDetails() const {
    cout << "Name: \t\t\t" << name
         << "\nAddress: \t\t" << address
         << "\nDOB: \t\t\t" << DOB
         << "\nPhone: \t\t\t" << telNumber << endl;
}

// Returns the name of the person
string Person::getName() const {
    return name;
}

// Returns the address of the person
string Person::getAddress() const {
    return address;
}

// Returns the date of birth of the person
string Person::getDOB() const {
    return DOB;
}

// Returns the telephone number of the person
string Person::getTelNumber() const {
    return telNumber;
}

// Sets the name of the person
void Person::setName(const string& name) {
    this->name = name;
}

// Sets the address of the person
void Person::setAddress(const string& address) {
    this->address = address;
}

// Sets the date of birth of the person, throws an error if the format is incorrect
void Person::setDOB(const string& dob) {
    if (validateDOB(dob)) {
        this->DOB = dob;
    } else {
        throw invalid_argument("Invalid date format. Expected 'dd/mm/yyyy', got '" + dob + "'. Please try again.");
    }
}

// Sets the telephone number of the person, throws an error if the format is incorrect
void Person::setTelNumber(const string& telNumber) {
    if (validateTelNumber(telNumber)) {
        this->telNumber = telNumber;
    } else {
        throw invalid_argument("Invalid telephone number format. Please try again.");
    }
}

// Validates the date of birth format (dd/mm/yyyy)
bool Person::validateDOB(const string& dob) {
    regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/\d{4}$)"); // Matches dd/mm/yyyy format
    return regex_match(dob, pattern);
}

// Validates the telephone number format (0XX-XXXXXXX)
bool Person::validateTelNumber(const string& telNumber) {
    regex pattern(R"(0\d{2}-\d{7})"); // Matches 0XX-XXXXXXX format
    return regex_match(telNumber, pattern);
}
