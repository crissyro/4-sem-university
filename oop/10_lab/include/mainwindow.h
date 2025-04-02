#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "teacherjournal.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addGroupButton_clicked();
    void on_addStudentButton_clicked();
    void on_addSubjectButton_clicked();
    void on_addGradeButton_clicked();
    void onGroupSelected(int index);
    void onStudentSelected(int index);

private:
    Ui::MainWindow *ui;
    TeacherJournal journal;
    
    void updateGroupsList();
    void updateStudentsList();
    void updateSubjectsList();
    void updateGradesTable();
    
    SmartPointer<Student> getSelectedStudent() const;
    SmartPointer<Subject> getSelectedSubject() const;
};

#endif // MAINWINDOW_H