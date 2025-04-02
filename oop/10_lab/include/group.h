#ifndef GROUP_H
#define GROUP_H

#include <QString>
#include <vector>
#include "smartpointer.h"
#include "student.h"

class Group {
    QString name;
    std::vector<SmartPointer<Student>> students;
public:
    explicit Group(const QString& name) : name(name) {}
    
    void addStudent(SmartPointer<Student> student) {
        students.push_back(std::move(student));
    }
    
    QString getName() const { 
        return name; 
    }

    const std::vector<SmartPointer<Student>>& getStudents() const { 
        return students; 
    }
};

#endif // GROUP_H