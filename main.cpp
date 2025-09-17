#include <iostream>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include <sstream>
#include <limits>

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
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// 27. Функция для удаления студента по имени
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

// ====== Тесты ======
// Тест для функции addStudent
TEST(StudentDatabase, AddStudentTest) {
    std::vector<Student> database;

    // Подготовка тестовых данных
    std::string input = "Бимбобик\n1\nСлеинг\n2.5\n";
    std::stringstream input_stream(input);

    // Сохраняет старый буфер std::cin и перенаправляет на тестовый ввод
    std::streambuf* old_cin = std::cin.rdbuf();
    std::cin.rdbuf(input_stream.rdbuf());

    // Вызывает функцию addStudent
    addStudent(database);

    // Восстанавливает std::cin
    std::cin.rdbuf(old_cin);
    
    // Проверяет результат
    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Бимбобик");
    EXPECT_EQ(database[0].age, 1);
    EXPECT_EQ(database[0].major, "Слеинг");
    EXPECT_NEAR(database[0].gpa, 2.5, 1e-6);
}

// Тест для функции displayStudents с пустой базой данных
TEST(StudentDatabase, DisplayEmptyDatabaseTest) {
    std::vector<Student> database;
    
    // Перехватываем вывод
    std::stringstream output_stream;
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(output_stream.rdbuf());
    
    displayStudents(database);
    
    // Восстанавливаем std::cout
    std::cout.rdbuf(old_cout);
    
    std::string output = output_stream.str();
    EXPECT_EQ(output, "Список студентов:\n"); // Ожидаем только заголовок при пустой базе
}

// Тест для функции displayStudents с несколькими студентами
TEST(StudentDatabase, DisplayMultipleStudentsTest) {
    std::vector<Student> database = {
        {"Пивич", 5, "Питинг", 5.0},
        {"Акакий", 999, "Ядерно-квантовая ржачка", 19.84}
    };
    
    // Перехватывает вывод
    std::stringstream output_stream;
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(output_stream.rdbuf());
    
    displayStudents(database);
    
    // Восстанавливает std::cout
    std::cout.rdbuf(old_cout);
    
    std::string output = output_stream.str();
    EXPECT_TRUE(output.find("Пивич") != std::string::npos);
    EXPECT_TRUE(output.find("Акакий") != std::string::npos);
    EXPECT_TRUE(output.find("Питинг") != std::string::npos);
    EXPECT_TRUE(output.find("Ядерно-квантовая ржачка") != std::string::npos);
    EXPECT_TRUE(output.find("5.0") != std::string::npos); // Проверяем GPA Пивича
    EXPECT_TRUE(output.find("19.84") != std::string::npos); // Проверяем GPA Акакия
}

// Тест для функции removeStudent с существующим студентом
TEST(StudentDatabase, RemoveStudentExistingTest) {
    std::vector<Student> database = {{"Бимбобик", 1, "Слеинг", 2.5}};
    
    // Подготовка тестовых данных
    std::string input = "Бимбобик\n";
    std::stringstream input_stream(input);

    // Сохраняет старый буфер std::cin и перенаправляет на тестовый ввод
    std::streambuf* old_cin = std::cin.rdbuf();
    std::cin.rdbuf(input_stream.rdbuf());

    // Перехватываем вывод
    std::stringstream output_stream;
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(output_stream.rdbuf());
    
    // Вызывает функцию removeStudent
    removeStudent(database);
    
    // Восстанавливает std::cin и std::cout
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);
    
    // Проверяет результат
    EXPECT_TRUE(database.empty());
    EXPECT_TRUE(output_stream.str().find("Студент удалён из базы данных") != std::string::npos);
}

// Тест для функции removeStudent с несуществующим студентом
TEST(StudentDatabase, RemoveStudentNonExistingTest) {
    std::vector<Student> database = {{"Бимбобик", 1, "Слеинг", 2.5}};
    
    // Подготовка тестовых данных
    std::string input = "Непонятный\n";
    std::stringstream input_stream(input);

    // Сохраняет старый буфер std::cin и перенаправляет на тестовый ввод
    std::streambuf* old_cin = std::cin.rdbuf();
    std::cin.rdbuf(input_stream.rdbuf());

    // Перехватываем вывод
    std::stringstream output_stream;
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(output_stream.rdbuf());
    
    // Вызывает функцию removeStudent
    removeStudent(database);
    
    // Восстанавливает std::cin и std::cout
    std::cin.rdbuf(old_cin);
    std::cout.rdbuf(old_cout);
    
    // Проверяет результат
    EXPECT_EQ(database.size(), 1);
    EXPECT_TRUE(output_stream.str().find("Студент с таким именем не найден") != std::string::npos);
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
    if (argc > 1) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } else {
        runInteractiveMode();
        return 0;
    }
}
