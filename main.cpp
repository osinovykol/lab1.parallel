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
// Тест 1: Unit-тест на добавление студента через меню
TEST(StudentDatabaseTest, AddStudent) {
    std::vector<Student> database;
    std::stringstream input("1\nAlice 20 CS 3.5\n");
    std::streambuf* old_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 1) addStudent(database);

    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Alice");
    EXPECT_EQ(database[0].age, 20);
    EXPECT_EQ(database[0].major, "CS");
    EXPECT_DOUBLE_EQ(database[0].gpa, 3.5);
    EXPECT_TRUE(output.str().find("Студент добавлен в базу данных") != std::string::npos);
}

// Тест 2: Unit-тест на удаление существующего студента через меню
TEST(StudentDatabaseTest, RemoveStudentExisting) {
    std::vector<Student> database = {{"Bob", 22, "Math", 4.0}};
    std::stringstream input("3\nBob\n");
    std::streambuf* old_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 3) removeStudent(database);

    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    EXPECT_EQ(database.size(), 0);
    EXPECT_TRUE(output.str().find("Студент удалён из базы данных") != std::string::npos);
}

// Тест 3: Unit-тест на удаление несуществующего студента через меню
TEST(StudentDatabaseTest, RemoveStudentNonExisting) {
    std::vector<Student> database = {{"Bob", 22, "Math", 4.0}};
    std::stringstream input("3\nAlice\n");
    std::streambuf* old_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 3) removeStudent(database);

    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    EXPECT_EQ(database.size(), 1);
    EXPECT_TRUE(output.str().find("Студент с таким именем не найден") != std::string::npos);
}

// Тест 4: Тест на вывод студентов (пустая база) через меню
TEST(StudentDatabaseTest, DisplayStudentsEmpty) {
    std::vector<Student> database;
    std::stringstream input("2\n");
    std::streambuf* old_cin = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    std::stringstream output;
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    int choice;
    std::cin >> choice;
    if (choice == 2) displayStudents(database);

    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);

    std::string expected = "Меню:\n1. Добавить студента\n2. Вывести список студентов\n3. Удалить студента\n0. Выход\nВыберите действие: Список студентов:\n";
    EXPECT_EQ(output.str().substr(0, expected.length()), expected);
}

// Тест 5: Тест на полный цикл (добавление + вывод + удаление) через меню
TEST(StudentDatabaseTest, FullCycle) {
    std::vector<Student> database;
    // Добавление
    {
        std::stringstream input("1\nCharlie 25 Physics 3.8\n");
        std::streambuf* old_cin = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());

        std::stringstream output;
        std::streambuf* old_cout = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        int choice;
        std::cin >> choice;
        if (choice == 1) addStudent(database);

        std::cin.rdbuf(old_cin);
        std::cout.rdbuf(old_cout);

        EXPECT_EQ(database.size(), 1);
        EXPECT_TRUE(output.str().find("Студент добавлен в базу данных") != std::string::npos);
    }

    // Вывод
    {
        std::stringstream input("2\n");
        std::streambuf* old_cin = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());

        std::stringstream output;
        std::streambuf* old_cout = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        int choice;
        std::cin >> choice;
        if (choice == 2) displayStudents(database);

        std::cin.rdbuf(old_cin);
        std::cout.rdbuf(old_cout);

        std::string expected = "Меню:\n1. Добавить студента\n2. Вывести список студентов\n3. Удалить студента\n0. Выход\nВыберите действие: Список студентов:\nИндекс: 0\nИмя: Charlie\nВозраст: 25\nСпециальность: Physics\nСредний балл: 3.8\n\n";
        EXPECT_EQ(output.str(), expected);
    }

    // Удаление
    {
        std::stringstream input("3\nCharlie\n");
        std::streambuf* old_cin = std::cin.rdbuf();
        std::cin.rdbuf(input.rdbuf());

        std::stringstream output;
        std::streambuf* old_cout = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        int choice;
        std::cin >> choice;
        if (choice == 3) removeStudent(database);

        std::cin.rdbuf(old_cin);
        std::cout.rdbuf(old_cout);

        EXPECT_EQ(database.size(), 0);
        EXPECT_TRUE(output.str().find("Студент удалён из базы данных") != std::string::npos);
    }
}

void runInteractiveMode() {
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
}

int main(int argc, char **argv) {
    // Если есть аргументы командной строки, запускает тесты
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        // Иначе запускает интерактивное меню
        runInteractiveMode();
        return 0;
    }
}
