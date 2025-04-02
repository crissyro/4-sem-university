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

    inline int getValue() const { 
        return value; 
    }

    inline QDate getDate() const { 
        return date;
    }

    inline const SmartPointer<Subject>& getSubject() const { 
        return subject; 
    }
};

#endif // GRADE_H