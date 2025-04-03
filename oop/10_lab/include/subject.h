#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>

class Subject {
    QString name;
public:
    explicit Subject(const QString& name) : name(name) {}

    QString getName() const { 
        return name;
    }
};

#endif // SUBJECT_H
