CC = g++
CFLAGS = -Werror -std=c++17

OS := $(shell uname)

ifeq ($(OS),Darwin)
    TEST_LIBS = -lcheck -lm
	OP = open
endif

ifeq ($(OS),Linux)
	OP = xdg-open
    TEST_LIBS = -lcheck -lm -lsubunit -lrt -pthread
endif

all: test

test:
	$(CC) $(CFLAGS) --coverage tests/*.cpp -lgtest -o test
	./test

gcov_report: clean test
	lcov -t "test" -o s21_test.info --no-external -c -d .
	genhtml -o report s21_test.info
	$(OP) ./report/index.html

clean:
	rm -rf *.o *.out *.a test
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

leaks: test
	valgrind --leak-check=full ./test

rebuild: clean all