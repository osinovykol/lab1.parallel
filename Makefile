CXX = g++
CXXFLAGS = -std=c++20 -Wall -g
LDFLAGS = -lgtest -lgtest_main -lpthread -lgcov

all: a.out

a.out: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o a.out $(LDFLAGS)

test: a.out
	./a.out --gtest_filter=*  # Явно запускаем все тесты

clean:
	rm -f a.out *.o *.gcda *.gcno *.gcov coverage.xml

coverage:
	./a.out --gtest_filter=*
	gcov main.cpp
	gcovr --xml --root . --exclude-unreachable-branches --exclude-throw-branches > coverage.xml
