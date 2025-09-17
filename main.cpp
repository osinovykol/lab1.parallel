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

// Новая функция: поиск студента по имени
void searchStudent(const std::vector<Student>& database) {
    std::string nameToSearch;
    std::cout << "Введите имя студента для поиска: ";
    std::cin >> nameToSearch;

    bool found = false;
    for (const auto& student : database) {
        if (student.name == nameToSearch) {
            std::cout << "Найден студент:\n";
            std::cout << "Имя: " << student.name << "\n";
            std::cout << "Возраст: " << student.age << "\n";
            std::cout << "Специальность: " << student.major << "\n";
            std::cout << "Средний балл: " << student.gpa << "\n\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Студент с таким именем не найден.\n";
    }
}

// ====== Тесты ======

#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

TEST(StudentFunctionsTest, AddStudent) {
    std::vector<Student> database;
    std::stringstream input;
    std::stringstream output;

    input << "1\n";  // Выбор действия: Добавить студента
    input << "Alice\n";  // Имя
    input << "20\n";     // Возраст
    input << "CS\n";     // Специальность
    input << "3.5\n";    // GPA

    auto* oldCin = std::cin.rdbuf(input.rdbuf());
    auto* oldCout = std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 1) addStudent(database);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    ASSERT_EQ(database.size(), 1u);
    EXPECT_EQ(database[0].name, "Alice");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "CS");
    EXPECT_DOUBLE_EQ(database[0].gpa, 3.5);
    EXPECT_NE(output.str().find("Студент добавлен в базу данных"), std::string::npos);
    EXPECT_NE(output.str().find("Введите имя студента"), std::string::npos);
}

TEST(StudentFunctionsTest, DisplayStudentsEmpty) {
    std::vector<Student> database;
    std::stringstream input;
    std::stringstream output;

    input << "2\n";  // Выбор действия: Вывести список студентов

    auto* oldCin = std::cin.rdbuf(input.rdbuf());
    auto* oldCout = std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 2) displayStudents(database);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    std::string out = output.str();
    EXPECT_NE(out.find("Список студентов:"), std::string::npos);
    EXPECT_EQ(out.find("Индекс:"), std::string::npos);
    EXPECT_NE(out.find("Меню:"), std::string::npos);
}

TEST(StudentFunctionsTest, DisplayStudentsNonEmpty) {
    std::vector<Student> database = {
        {"Bob", 22, "Math", 4.0},
        {"Carol", 19, "Bio", 3.9}
    };
    std::stringstream input;
    std::stringstream output;

    input << "2\n";  // Выбор действия: Вывести список студентов

    auto* oldCin = std::cin.rdbuf(input.rdbuf());
    auto* oldCout = std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 2) displayStudents(database);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    std::string out = output.str();
    EXPECT_NE(out.find("Индекс: 0"), std::string::npos);
    EXPECT_NE(out.find("Имя: Bob"), std::string::npos);
    EXPECT_NE(out.find("Возраст: 22"), std::string::npos);
    EXPECT_NE(out.find("Специальность: Math"), std::string::npos);
    EXPECT_NE(out.find("Средний балл: 4"), std::string::npos);
    EXPECT_NE(out.find("Индекс: 1"), std::string::npos);
    EXPECT_NE(out.find("Имя: Carol"), std::string::npos);
    EXPECT_NE(out.find("Меню:"), std::string::npos);
}

TEST(StudentFunctionsTest, RemoveStudentExisting) {
    std::vector<Student> database = {{"Dave", 21, "Art", 3.2}};
    std::stringstream input;
    std::stringstream output;

    input << "3\n";  // Выбор действия: Удалить студента
    input << "Dave\n"; // Имя для удаления

    auto* oldCin = std::cin.rdbuf(input.rdbuf());
    auto* oldCout = std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 3) removeStudent(database);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    EXPECT_TRUE(database.empty());
    EXPECT_NE(output.str().find("Студент удалён из базы данных"), std::string::npos);
    EXPECT_NE(output.str().find("Введите имя студента для удаления"), std::string::npos);
}

TEST(StudentFunctionsTest, RemoveStudentNonExisting) {
    std::vector<Student> database = {{"Eve", 23, "Chem", 3.7}};
    std::stringstream input;
    std::stringstream output;

    input << "3\n";  // Выбор действия: Удалить студента
    input << "Mallory\n"; // Несуществующее имя

    auto* oldCin = std::cin.rdbuf(input.rdbuf());
    auto* oldCout = std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 3) removeStudent(database);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    EXPECT_EQ(database.size(), 1u);
    EXPECT_NE(output.str().find("Студент с таким именем не найден"), std::string::npos);
    EXPECT_NE(output.str().find("Введите имя студента для удаления"), std::string::npos);
}

// Новый тест для функции searchStudent
TEST(StudentFunctionsTest, SearchStudentExisting) {
    std::vector<Student> database = {
        {"Frank", 24, "Physics", 3.8},
        {"Grace", 20, "CS", 3.9}
    };
    std::stringstream input;
    std::stringstream output;

    input << "4\n";  // Выбор действия: Поиск студента
    input << "Frank\n"; // Имя для поиска

    auto* oldCin = std::cin.rdbuf(input.rdbuf());
    auto* oldCout = std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 4) searchStudent(database);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    std::string out = output.str();
    EXPECT_NE(out.find("Найден студент:"), std::string::npos);
    EXPECT_NE(out.find("Имя: Frank"), std::string::npos);
    EXPECT_NE(out.find("Возраст: 24"), std::string::npos);
    EXPECT_NE(out.find("Специальность: Physics"), std::string::npos);
    EXPECT_NE(out.find("Средний балл: 3.8"), std::string::npos);
    EXPECT_NE(out.find("Введите имя студента для поиска"), std::string::npos);
    EXPECT_NE(out.find("Меню:"), std::string::npos);
}

// Новый тест для функции searchStudent (несуществующий студент)
TEST(StudentFunctionsTest, SearchStudentNonExisting) {
    std::vector<Student> database = {
        {"Frank", 24, "Physics", 3.8}
    };
    std::stringstream input;
    std::stringstream output;

    input << "4\n";  // Выбор действия: Поиск студента
    input << "Helen\n"; // Несуществующее имя

    auto* oldCin = std::cin.rdbuf(input.rdbuf());
    auto* oldCout = std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 4) searchStudent(database);

    std::cin.rdbuf(oldCin);
    std::cout.rdbuf(oldCout);

    std::string out = output.str();
    EXPECT_NE(out.find("Студент с таким именем не найден"), std::string::npos);
    EXPECT_NE(out.find("Введите имя студента для поиска"), std::string::npos);
    EXPECT_NE(out.find("Меню:"), std::string::npos);
}

void runInteractiveMode() {
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Удалить студента\n";
        std::cout << "4. Поиск студента\n"; // Новый пункт меню
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
            case 4:
                searchStudent(database); // Новый случай
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        runInteractiveMode();
        return 0;
    }
}
