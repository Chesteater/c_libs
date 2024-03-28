CFLAGS=-Wall -Werror -Wextra
LIBS=-lcheck
GCOV=-fprofile-arcs -ftest-coverage
OBJECTS=our_math.o

SOURSES=our_math.c

all: main
main: clean our_math.a test gcov_report
our_math.a: 
	gcc $(CFLAGS) -c $(SOURSES)  
	ar rcs our_math.a $(OBJECTS)

test: our_math.a test

test:
	python3 ../materials/linters/cpplint.py --extensions=c our_math.c
	python3 ../materials/linters/cpplint.py --extensions=c our_math.h
	python3 ../materials/linters/cpplint.py --extensions=c unit_test.c
	gcc $(CFLAGS) -c unit_test.c  -o unit_test.o
	gcc $(CFLAGS) unit_test.o our_math.a  $(LIBS) -o test
	./test

gcov_report: our_math.a
	gcc $(CFLAGS) $(GCOV) unit_test.c $(LIBS) $(SOURSES) -o GcovReport
	./GcovReport
	lcov -t "GcovReport" -o GcovReport.info -c -d .
	genhtml -o report GcovReport.info 
	open ./report/index-sort-f.html
	rm -rf ./*.gcno ./*.gcda ./GcovReport.*

clean:
	rm -rf ./*.o ./*.a ./a.out ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./math_o

rebuild: clean all
