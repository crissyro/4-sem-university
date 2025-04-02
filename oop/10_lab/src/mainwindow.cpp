#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QListWidget>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    ui->gradesTable->setColumnCount(3);
    ui->gradesTable->setHorizontalHeaderLabels({"Предмет", "Оценка", "Дата"});
    
    connect(ui->groupsList, &QListWidget::currentRowChanged,
            this, &MainWindow::onGroupSelected);
    connect(ui->studentsList, &QListWidget::currentRowChanged,
            this, &MainWindow::onStudentSelected);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addGroupButton_clicked() {
    bool ok;
    QString name = QInputDialog::getText(
        this, 
        "Новая группа", 
        "Введите название группы:", 
        QLineEdit::Normal, 
        "", 
        &ok
    );
    
    if (ok && !name.isEmpty()) {
        journal.addGroup(SmartPointer<Group>(new Group(name)));
        updateGroupsList();
    }
}

void MainWindow::updateGroupsList() {
    ui->groupsList->clear();
    for (const auto& group : journal.getGroups()) {
        ui->groupsList->addItem(group->getName());
    }
}

void MainWindow::onGroupSelected(int index) {
    if (index >= 0 && static_cast<size_t>(index) < journal.getGroups().size()) {
        updateStudentsList();
    }
}

void MainWindow::updateStudentsList() {
    ui->studentsList->clear();
    int groupIndex = ui->groupsList->currentRow();

    if (groupIndex < 0) {
        return;
    }

    const auto& students = journal.getGroups()[groupIndex]->getStudents();
    for (const auto& student : students) {
        ui->studentsList->addItem(
            student->getLastName() + " " + student->getFirstName()
        );
    }
}

void MainWindow::on_addStudentButton_clicked() {
    if(ui->groupsList->currentRow() < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите группу!");
        return;
    }
    
    bool ok;
    QString firstName = QInputDialog::getText(
        this, "Новый студент", "Имя:", QLineEdit::Normal, "", &ok);
    
    QString lastName = QInputDialog::getText(
        this, "Новый студент", "Фамилия:", QLineEdit::Normal, "", &ok);
    
    if(ok && !firstName.isEmpty() && !lastName.isEmpty()) {
        int groupIndex = ui->groupsList->currentRow();
        auto& group = journal.getGroups()[groupIndex];
        group->addStudent(SmartPointer<Student>(new Student(firstName, lastName)));
        updateStudentsList();
    }
}

void MainWindow::on_addSubjectButton_clicked() {
    bool ok;
    QString name = QInputDialog::getText(
        this, "Новый предмет", "Название:", QLineEdit::Normal, "", &ok);
    
    if(ok && !name.isEmpty()) {
        journal.addSubject(SmartPointer<Subject>(new Subject(name)));
        updateSubjectsList();
    }
}

void MainWindow::on_addGradeButton_clicked() {
    Student* student = getSelectedStudent();
    Subject* subject = getSelectedSubject();
    
    if(!student || !subject) {
        QMessageBox::warning(this, "Ошибка", "Выберите студента и предмет!");
        return;
    }
    
    bool ok;
    const int value = QInputDialog::getInt(
        this, "Новая оценка", "Введите оценку (1-5):", 3, 1, 5, 1, &ok);
    
    if(ok) {
        try {
            const QDate date = QDate::currentDate();
            auto newSubject = MakeSmart<Subject>(subject->getName());
            student->addGrade(MakeSmart<Grade>(
                value, 
                date, 
                std::move(newSubject)
            ));
            updateGradesTable();
        } 
        catch(const std::exception& e) {
            QMessageBox::critical(this, "Ошибка", e.what());
        }
    }
}

void MainWindow::updateSubjectsList() {
    ui->subjectsComboBox->clear();
    for(const auto& subject : journal.getSubjects()) {
        ui->subjectsComboBox->addItem(subject->getName());
    }
}

void MainWindow::updateGradesTable() {
    ui->gradesTable->setRowCount(0);
    
    if(auto student = getSelectedStudent()) {
        const auto& grades = student->getGrades();
        ui->gradesTable->setRowCount(grades.size());
        
        for(int row = 0; row < static_cast<int>(grades.size()); ++row) {
            const auto& grade = grades[row]; 
            if(grade) {
                QString subjectName = grade->getSubject() 
                    ? grade->getSubject()->getName() 
                    : "Неизвестный предмет";
                
                ui->gradesTable->setItem(row, 0, new QTableWidgetItem(subjectName));
                ui->gradesTable->setItem(row, 1, 
                    new QTableWidgetItem(QString::number(grade->getValue())));
                ui->gradesTable->setItem(row, 2, 
                    new QTableWidgetItem(grade->getDate().toString("dd.MM.yyyy")));
            }
        }
    }
}

Student* MainWindow::getSelectedStudent() const {
    const int groupIndex = ui->groupsList->currentRow();
    const int studentIndex = ui->studentsList->currentRow();
    
    if(groupIndex >= 0 && studentIndex >= 0) {
        const auto& groups = journal.getGroups();
        if(groupIndex < static_cast<int>(groups.size())) {
            const auto& students = groups[groupIndex]->getStudents();
            if(studentIndex < static_cast<int>(students.size())) {
                return students[studentIndex].get(); // Возвращаем сырой указатель
            }
        }
    }
    return nullptr;
}

Subject* MainWindow::getSelectedSubject() const {
    const int index = ui->subjectsComboBox->currentIndex();
    const auto& subjects = journal.getSubjects();
    
    if(index >= 0 && index < static_cast<int>(subjects.size())) {
        return subjects[index].get(); 
    }
    
    return nullptr;
}

void MainWindow::onStudentSelected(int index) {
    Q_UNUSED(index); 
    updateGradesTable();
}