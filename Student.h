#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Student {
    std::string lastName;
    std::string firstName;
    std::string group;
    int id;
};

class StudentList {
private:
    std::vector<Student> students;

public:
    void addStudent(const Student& student);
    
    std::vector<std::pair<std::string, std::string>> getStudentByIndex(int index);
    std::vector<Student> getAllStudents() const {
        return students;
    }
    void removeStudentById(int id);
    std::vector<int> findStudentsByName(const std::string& lastName, const std::string& firstName);
    std::vector<std::pair<std::string, std::string>> getStudentsByGroup(const std::string& group);
};

#endif // STUDENT_H




