#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <vector>
#include "smartpointer.h"
#include "grade.h"

class Student {
    QString firstName;
    QString lastName;
    std::vector<SmartPointer<Grade>> grades;
public:
    Student(const QString& firstName, const QString& lastName)
        : firstName(firstName), lastName(lastName) {}
    
    inline void addGrade(SmartPointer<Grade> grade) {
        grades.push_back(std::move(grade));
    }
    
    inline QString getFirstName() const { 
        return firstName; 
    }

    inline QString getLastName() const { 
        return lastName;
    }

    inline const std::vector<SmartPointer<Grade>>& getGrades() const { 
        return grades; 
    }
};

#endif // STUDENT_H