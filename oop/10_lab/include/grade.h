#ifndef GRADE_H
#define GRADE_H

#include <QDate>
#include "smartpointer.h"
#include "subject.h"

class Grade {
    int value;
    QDate date;
    SmartPointer<Subject> subject;
public:
    Grade(int value, const QDate& date, SmartPointer<Subject>&& subject)
        : value(value), date(date), subject(std::move(subject)) {}

    int getValue() const { 
        return value; 
    }

    QDate getDate() const { 
        return date;
    }

    const SmartPointer<Subject>& getSubject() const { 
        return subject; 
    }
};

#endif // GRADE_H