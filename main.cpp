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

// Функция для добавления студента в базу данных
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

// Функция для вывода всех студентов из базы данных
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

// Функция для удаления студента по имени
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

// Функция для эмуляции меню
void runMenu(std::vector<Student>& database, const std::string& inputData) {
    input.str(inputData);
    std::cin.rdbuf(input.rdbuf());
    std::cout.rdbuf(output.rdbuf());

    int choice;
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
}

// Тест 1: Unit-тест на добавление студента через меню
TEST(StudentDatabaseTest, AddStudent) {
    std::vector<Student> database;
    input.str("1\nAlice 20 CS 3.5\n"); // Выбор 1 + данные студента
    runMenu(database, input.str());
    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Alice");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "CS");
    EXPECT_DOUBLE_EQ(database[0].gpa, 3.5);
    output.str("");
}

// Тест 2: Unit-тест на удаление существующего студента через меню
TEST(StudentDatabaseTest, RemoveStudentExisting) {
    std::vector<Student> database = {{"Bob", 22, "Math", 4.0}};
    input.str("3\nBob\n"); // Выбор 3 + имя для удаления
    runMenu(database, input.str());
    EXPECT_EQ(database.size(), 0);
    output.str("");
}

// Тест 3: Unit-тест на удаление несуществующего студента через меню
TEST(StudentDatabaseTest, RemoveStudentNonExisting) {
    std::vector<Student> database = {{"Bob", 22, "Math", 4.0}};
    input.str("3\nAlice\n"); // Выбор 3 + несуществующее имя
    runMenu(database, input.str());
    EXPECT_EQ(database.size(), 1);
    output.str("");
}

// Тест 4: Тест на вывод студентов (пустая база) через меню
TEST(StudentDatabaseTest, DisplayStudentsEmpty) {
    std::vector<Student> database;
    input.str("2\n"); // Выбор 2
    runMenu(database, input.str());
    std::string expected = "Меню:\n1. Добавить студента\n2. Вывести список студентов\n3. Удалить студента\n0. Выход\nВыберите действие: Список студентов:\n";
    EXPECT_EQ(output.str(), expected);
    output.str("");
}

// Тест 5: Тест на полный цикл (добавление + вывод + удаление) через меню
TEST(StudentDatabaseTest, FullCycle) {
    std::vector<Student> database;
    // Добавление
    input.str("1\nCharlie 25 Physics 3.8\n");
    runMenu(database, input.str());
    EXPECT_EQ(database.size(), 1);
    output.str("");

    // Вывод
    input.str("2\n");
    runMenu(database, input.str());
    std::string expected = "Меню:\n1. Добавить студента\n2. Вывести список студентов\n3. Удалить студента\n0. Выход\nВыберите действие: Список студентов:\nИндекс: 0\nИмя: Charlie\nВозраст: 25\nСпециальность: Physics\nСредний балл: 3.8\n\n";
    EXPECT_EQ(output.str(), expected);
    output.str("");

    // Удаление
    input.str("3\nCharlie\n");
    runMenu(database, input.str());
    EXPECT_EQ(database.size(), 0);
    output.str("");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    if (argc > 1) {
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
