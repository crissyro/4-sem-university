QT += core gui widgets
TARGET = VirtualTeacherJournal
TEMPLATE = app

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/teacherjournal.cpp
    
HEADERS += include/mainwindow.h include/smartpointer.h include/subject.h \
           include/grade.h include/student.h include/group.h include/teacherjournal.h

FORMS += forms/mainwindow.ui  # Если используется Qt Designer