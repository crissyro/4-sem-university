#include "../include/teacherjournal.h"

void TeacherJournal::addGroup(SmartPointer<Group> group) {
    groups.push_back(std::move(group));
}

void TeacherJournal::addSubject(SmartPointer<Subject> subject) {
    subjects.push_back(std::move(subject));
}

const std::vector<SmartPointer<Group>>& TeacherJournal::getGroups() const {
    return groups;
}

const std::vector<SmartPointer<Subject>>& TeacherJournal::getSubjects() const {
    return subjects;
}