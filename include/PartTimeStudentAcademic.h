#ifndef PARTTIMESTUDENTACADEMIC_H
#define PARTTIMESTUDENTACADEMIC_H

#include "PartTimeAcademic.h"

// PartTimeStudentAcademic class inherits from PartTimeAcademic
// This class represents a student who is also employed part-time
class PartTimeStudentAcademic : public PartTimeAcademic {
public:
    // Constructor to initialize a PartTimeStudentAcademic with personal and employment details
    // Inherits constructor from PartTimeAcademic
    PartTimeStudentAcademic(const string& name, const string& address, const string& DOB, const string& telNumber,
                            const string& studentNumber, int hoursWorked);

    void printDetails() const override;
    double calculatePay() const override;
};

#endif
