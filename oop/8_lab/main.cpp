#include "queue.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>


struct Student {
    std::string surname;
    int age;
    int score;

    Student() : age(0), score(0) {}
    Student(const std::string& s, int a, int sc) : surname(s), age(a), score(sc) {}
};

Queue<Student> readStudentsFromFile(const std::string& filename) {
    Queue<Student> queue;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string surname;
        int age, score;
        if (iss >> surname >> age >> score) {
            queue.enqueue(Student(surname, age, score));
        }
    }

    return queue;
}

template<typename T, typename V>
bool compareField(const T& obj, V value, V T::* member) {
    return obj.*member == value;
}

template<typename T, typename V>
std::vector<T> searchInQueue(Queue<T>& queue, V value, V T::* member) {
    std::vector<T> results;
    for (auto it = queue.begin(); it != queue.end(); ++it) {
        if (compareField(*it, value, member)) {
            results.push_back(*it);
        }
    }

    return results;
}


int main() {
    try {
        Queue<Student> students = readStudentsFromFile("students.txt");
        
        int targetAge = 20;
        auto byAge = searchInQueue(students, targetAge, &Student::age);
        std::cout << "Students with age " << targetAge << ":\n";
        for (const auto& s : byAge) {
            std::cout << s.surname << " " << s.age << " " << s.score << std::endl;
        }

        int targetScore = 5;
        auto byScore = searchInQueue(students, targetScore, &Student::score);
        std::cout << "Students with score " << targetScore << ":\n";
        for (const auto& s : byScore) {
            std::cout << s.surname << " " << s.age << " " << s.score << std::endl;
        }

        std::string targetSurname = "Ivanov";
        auto bySurname = searchInQueue(students, targetSurname, &Student::surname);
        std::cout << "Students with surname " << targetSurname << ":\n";
        for (const auto& s : bySurname) {
            std::cout << s.surname << " " << s.age << " " << s.score << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}