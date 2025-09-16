CXX = g++
CXXFLAGS = -std=c++20 -Wall -g  # -g для отладки и покрытия
LDFLAGS = -lgtest -lgtest_main -lpthread -lgcov  # Для тестов и покрытия

all: a.out

a.out: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o a.out $(LDFLAGS)

test: a.out
	./a.out  # Запуск тестов (поскольку в main.cpp if argc>1 не обязательно, но RUN_ALL_TESTS() запустится если init)

clean:
	rm -f a.out *.o *.gcda *.gcno *.gcov

coverage:
	gcov main.cpp  # Для генерации покрытия после тестов
