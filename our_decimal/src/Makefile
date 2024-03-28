CC = gcc
GCOVFLAGS = -lgcov --coverage

SOURCES = $(wildcard our_*.c)
TESTS_SOURSES = $(wildcard ./tests/*.check)
TESTS = $(TESTS_SOURSES:.check=.test)
OBJECTS = $(SOURCES:.c=.o)

all: clean our_decimal.a

our_decimal.a: $(OBJECTS) our_decimal.h 
	ar rc $@ $(OBJECTS)
	ranlib $@

lib_cov.a: $(SOURCES) our_decimal.h
	$(CC) $(CFLAGS) -c *.c -g $(GCOVFLAGS)
	ar rc $@ *.o
	ranlib $@

gcov_report: clean lib_cov.a

	$(CC) tests.c -c -g 
	$(CC) tests.o -g -L. -lcheck lib_cov.a -o GcovReport $(GCOVFLAGS)
	-./GcovReport
	lcov -t "GcovReport" -o GcovReport.info -c -d .
	genhtml -o report GcovReport.info 
	open ./report/index-sort-f.html
	rm -rf ./*.gcno ./*.gcda ./GcovReport.*

test: clean clang_formating $(TESTS_SOURSES) our_decimal.a
	$(CC) -o test tests.c our_decimal.a -lcheck 
	./test

clean:
	rm -rf *.a *.o *.gcda *.gcno *.info report test *.input *.output */*.exe

clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -n *.c

clang_formating:
		clang-format --style=google -i *.c

gcov_lcov_install:
		cd ~/goinfre
		mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
		eval "$(homebrew/bin/brew shellenv)"
		brew update --force --quiet
		chmod -R go-w "$(brew --prefix)/share/zsh"
		brew install lcov