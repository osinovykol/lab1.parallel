CXX = g++
CXXFLAGS = -std=c++20 -Wall -g -fprofile-arcs -ftest-coverage
LDFLAGS = -lgtest -lgtest_main -lpthread -lgcov

all: a.out

a.out: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o a.out $(LDFLAGS)

test: a.out
	./a.out --gtest_filter=*  # Запускаем все тесты
	@echo "Тесты завершены. Проверьте вывод выше на ошибки."

clean:
	rm -f a.out *.o *.gcda *.gcno *.gcov coverage.xml

coverage: a.out
	./a.out --gtest_filter=*  # Запускаем тесты для сбора данных покрытия
	$(CXX) $(CXXFLAGS) main.cpp -o a.out $(LDFLAGS)  # Пересборка с флагами покрытия (если нужно)
	gcov main.cpp
	gcovr --xml --root . --exclude-unreachable-branches --exclude-throw-branches -o coverage.xml
	@echo "Отчёт покрытия сохранён в coverage.xml. Проверьте файл."
