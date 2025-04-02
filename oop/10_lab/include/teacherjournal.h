#ifndef TEACHERJOURNAL_H
#define TEACHERJOURNAL_H

#include <vector>
#include "smartpointer.h"
#include "group.h"
#include "subject.h"

class TeacherJournal {
    std::vector<SmartPointer<Group>> groups;
    std::vector<SmartPointer<Subject>> subjects;
    
public:
    void addGroup(SmartPointer<Group> group);
    void addSubject(SmartPointer<Subject> subject);
    
    const std::vector<SmartPointer<Group>>& getGroups() const;
    const std::vector<SmartPointer<Subject>>& getSubjects() const;
};

#endif // TEACHERJOURNAL_H