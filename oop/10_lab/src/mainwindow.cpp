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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addGroupButton_clicked()
{
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

void MainWindow::updateGroupsList()
{
    ui->groupsList->clear();
    for (const auto& group : journal.getGroups()) {
        ui->groupsList->addItem(group->getName());
    }
}

void MainWindow::onGroupSelected(int index)
{
    if (index >= 0 && static_cast<size_t>(index) < journal.getGroups().size()) {
        updateStudentsList();
    }
}

void MainWindow::updateStudentsList()
{
    ui->studentsList->clear();
    int groupIndex = ui->groupsList->currentRow();
    if (groupIndex < 0) return;
    
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
    auto student = getSelectedStudent();
    auto subject = getSelectedSubject();
    
    if(!student || !subject) {
        QMessageBox::warning(this, "Ошибка", "Выберите студента и предмет!");
        return;
    }
    
    bool ok;
    int value = QInputDialog::getInt(
        this, "Новая оценка", "Введите оценку (1-5):", 3, 1, 5, 1, &ok);
    
    if(ok) {
        QDate date = QDate::currentDate();
        student->addGrade(SmartPointer<Grade>(
            new Grade(value, date, std::move(subject))
        ));
        updateGradesTable();
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
    auto student = getSelectedStudent();
    
    if(student) {
        int row = 0;
        for(const auto& grade : student->getGrades()) {
            ui->gradesTable->insertRow(row);
            ui->gradesTable->setItem(row, 0, 
                new QTableWidgetItem(grade->getSubject()->getName()));
            ui->gradesTable->setItem(row, 1, 
                new QTableWidgetItem(QString::number(grade->getValue())));
            ui->gradesTable->setItem(row++, 2, 
                new QTableWidgetItem(grade->getDate().toString("dd.MM.yyyy")));
        }
    }
}

SmartPointer<Student> MainWindow::getSelectedStudent() const {
    int groupIndex = ui->groupsList->currentRow();
    int studentIndex = ui->studentsList->currentRow();
    
    if(groupIndex >= 0 && studentIndex >= 0) {
        const auto& groups = journal.getGroups();
        if(static_cast<size_t>(groupIndex) < groups.size()) {
            const auto& students = groups[groupIndex]->getStudents();
            if(static_cast<size_t>(studentIndex) < students.size()) {
                return SmartPointer<Student>(students[studentIndex].get());
            }
        }
    }
    return SmartPointer<Student>();
}

SmartPointer<Subject> MainWindow::getSelectedSubject() const {
    int index = ui->subjectsComboBox->currentIndex();
    const auto& subjects = journal.getSubjects();
    
    if(index >= 0 && static_cast<size_t>(index) < subjects.size()) {
        return SmartPointer<Subject>(subjects[index].get());
    }
    return SmartPointer<Subject>(); 
}

void MainWindow::onStudentSelected(int index) {
    Q_UNUSED(index); // Подавляем предупреждение о неиспользуемой переменной
    
    // Обновляем таблицу оценок при выборе студента
    updateGradesTable();
}