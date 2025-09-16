#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <sstream>

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

void displayStudents(const std::vector<Student>& database) {
    std::cout << "Список студентов:\n";
    for (size_t i = 0; i < database.size(); ++i) {
        const Student& student = database[i];
        std::cout << "Индекс: " << i << "\n";
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

void removeStudent(std::vector<Student>& database) {
    std::string nameToRemove;
    std::cout << "Введите имя студента для удаления: ";
    std::cin >> nameToRemove;

    auto it = database.begin();
    while (it != database.end()) {
        if (it->name == nameToRemove) {
            it = database.erase(it);
            std::cout << "Студент удалён из базы данных.\n";
            return;
        } else {
            ++it;
        }
    }
    std::cout << "Студент с таким именем не найден.\n";
}

// Тесты
std::istringstream input;
std::ostringstream output;

// Тест 1: Unit-тест на добавление студента
TEST(StudentDatabaseTest, AddStudent) {
    std::vector<Student> database;
    input.str("Alice 20 CS 3.5\n");
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());
    addStudent(database);
    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Alice");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "CS");
    EXPECT_DOUBLE_EQ(database[0].gpa, 3.5);
    output.str("");
}

// Тест 2: Unit-тест на удаление существующего студента
TEST(StudentDatabaseTest, RemoveStudentExisting) {
    std::vector<Student> database = {{"Bob", 22, "Math", 4.0}};
    input.str("Bob\n");
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());
    removeStudent(database);
    EXPECT_EQ(database.size(), 0);
    output.str("");
}

// Тест 3: Unit-тест на удаление несуществующего студента
TEST(StudentDatabaseTest, RemoveStudentNonExisting) {
    std::vector<Student> database = {{"Bob", 22, "Math", 4.0}};
    input.str("Alice\n");
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());
    removeStudent(database);
    EXPECT_EQ(database.size(), 1);
    output.str("");
}

// Тест 4: Тест на вывод студентов (пустая база)
TEST(StudentDatabaseTest, DisplayStudentsEmpty) {
    std::vector<Student> database;
    std::cout.rdbuf(output.rdbuf());
    displayStudents(database);
    EXPECT_EQ(output.str(), "Список студентов:\n");
    output.str("");
}

// Тест 5: Тест на полный цикл (добавление + вывод + удаление)
TEST(StudentDatabaseTest, FullCycle) {
    std::vector<Student> database;
    input.str("Charlie 25 Physics 3.8\n");
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());
    addStudent(database);
    EXPECT_EQ(database.size(), 1);
    output.str("");

    displayStudents(database);
    std::string expected = "Список студентов:\nИндекс: 0\nИмя: Charlie\nВозраст: 25\nСпециальность: Physics\nСредний балл: 3.8\n\n";
    EXPECT_EQ(output.str(), expected);
    output.str("");

    input.str("Charlie\n");
    std::cin.rdbuf(input.rdbuf());
    removeStudent(database);
    EXPECT_EQ(database.size(), 0);
    output.str("");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    if (argc > 1 || ::testing::GTEST_FLAG(list_tests) || ::testing::GTEST_FLAG(filter) != NULL) {
        return RUN_ALL_TESTS();
    }

    std::vector<Student> database;
    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Удалить студента\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                removeStudent(database);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
