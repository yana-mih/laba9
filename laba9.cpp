#include "student.h"

void StudentList::addStudent(const Student& student) {
    auto it = std::find_if(students.begin(), students.end(), [&](const Student& s) {
        return s.id == student.id;
        });

    if (it != students.end()) {
        throw std::runtime_error("Student with the same ID already exists in the list.");
    }

    students.push_back(student);
}

void StudentList::removeStudentById(int id) {
    auto it = std::find_if(students.begin(), students.end(), [&](const Student& s) {
        return s.id == id;
        });

    if (it == students.end()) {
        throw std::runtime_error("Student with the specified ID does not exist in the list.");
    }

    students.erase(it);
}

std::vector<std::pair<std::string, std::string>> StudentList::getStudentByIndex(int index) {
    std::vector<std::pair<std::string, std::string>> names; 
    for (const auto& student : students) {
        if (student.id == index) {
            names.push_back({ student.lastName, student.firstName });
        }
    }
    return names;
}

std::vector<int> StudentList::findStudentsByName(const std::string& lastName, const std::string& firstName) {
    std::vector<int> positions;
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i].lastName == lastName && students[i].firstName == firstName) {
            positions.push_back(i);
        }
    }
    return positions;
}

std::vector<std::pair<std::string, std::string>> StudentList::getStudentsByGroup(const std::string& group) {
    std::vector<std::pair<std::string, std::string>> names;
    for (const auto& student : students) {
        if (student.group == group) {
            names.push_back({ student.lastName, student.firstName });
        }
    }
    return names;
}
int main() {
    std::system("chcp 1251");
    setlocale(LC_ALL, "RU");

    StudentList studentList;

    Student student1 = { "Смит", "Джон", "CS101", 1 };
    Student student2 = { "Джонсон", "Эмили", "CS101", 2 };

    try {
        studentList.addStudent(student1);
        studentList.addStudent(student2);

        std::vector<Student> students = studentList.getAllStudents();
        std::cout << "Список всех студентов:" << std::endl;
        for (const auto& student : students) {
            std::cout << "ID: " << student.id << ", Имя и фамилия: " << student.firstName << " " << student.lastName << ", Группа: " << student.group << std::endl;
           
        } 
        std::cout << "----------------------------------------------------" << std::endl;

        // Получаем информацию о студенте перед удалением
        std::vector<Student> allStudents = studentList.getAllStudents();
        std::string deletedFirstName, deletedLastName;

        for (const auto& student : allStudents) {
            if (student.id == 2) {
                deletedFirstName = student.firstName;
                deletedLastName = student.lastName;
                break;
            }
        }

        // Удаляем студента
        studentList.removeStudentById(2);

        // Выводим информацию об удаленном студенте
        std::cout << "Удаление студента: " << deletedFirstName << " " << deletedLastName << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;

        std::vector<Student> remainingStudents = studentList.getAllStudents();
        std::cout << "Оставшиеся студенты:" << std::endl;
        for (const auto& student : remainingStudents) {
            std::cout << "ID: " << student.id << ", Имя и фамилия: " << student.firstName << " " << student.lastName << ", Группа: " << student.group << std::endl;
            std::cout << "----------------------------------------------------" << std::endl;
        }

        std::vector<std::pair<std::string, std::string>> studentsInGroup = studentList.getStudentsByGroup("CS101");
        std::cout << "Студенты в группе CS101:" << std::endl;
        for (const auto& name : studentsInGroup) {
            std::cout << name.second << " " << name.first << std::endl;
            std::cout << "----------------------------------------------------" << std::endl;
        }

        std::vector<std::pair<std::string, std::string>> studentsByIndex = studentList.getStudentByIndex(1);
        std::cout << "Студент с ID 1:" << std::endl;
        for (const auto& student : studentsByIndex) {
            std::cout << student.second << " " << student.first << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
