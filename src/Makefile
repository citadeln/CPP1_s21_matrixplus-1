CC = g++ -std=c++17
#CC = gcc -Wall -Werror -Wextra -std=c++17
# FLAGS = -lgtest -lm -lsubunit -lstdc++ -ftest-coverage -fprofile-arcs

OS = $(shell uname)
ifeq ($(OS), Linux)
FLAGS=`pkg-config --cflags --libs gtest` -lm -g
else
FLAGS= -lm -lgtest -g
endif

all: s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) $(FLAGS) -c *.cc
	ar -crs s21_matrix_oop.a *.o 
# удалить ar -crs s21_matrix_oop.a *.o  зачем архив?

test: clean s21_matrix_oop.a
	$(CC) tests/test.cc s21_matrix_oop.a $(FLAGS) -o test
	./test

# gcov_report:
# 	$(MAKE) clean
# 	$(MAKE) test $(FLAGS) --coverage
# 	gcovr --html-details ./gcov_report.html 
# 	gcovr --xml ./build/cov.xm
# 	ln -s ./gcov_report.html ./gcov_report.html
# # @rm -rf *.gcno *gcda *.gco
# 	if [ ! -f ./gcov_report.html ]; then echo; echo "Ошибка. Проверьте доступность gcovr."; echo; fi
# 	if [ -f ./gcov_report.html ]; then echo; echo "Отчет сгенерирован в gcov_report.html"; echo; fi

gcov_report:
	@$(MAKE) clean
	@$(MAKE) test FLAGS="--coverage $(FLAGS)"
	@gcovr --html-details ./gcov_report.html 
	@gcovr --xml ./build/cov.xml
	@ln -s ./gcov_report.html ./gcov_report.html
# @if [ ! -f ./gcov_report.html ]; then echo; echo "Ошибка. Проверьте доступность gcovr."; echo; fi
# @if [ -f ./gcov_report.html ]; then echo; echo "Отчет сгенерирован в gcov_report.html";	echo; fi
# @xdg-open gcov_report.html

debug: clean
	$(MAKE) s21_matrix_oop.a >/dev/null
	$(CC) $(FLAGS) debug/*.cc -L. -l:s21_matrix_oop.a -o debug/debug.out -lstdc++ -lgtest -lgtest_main
	echo;debug/debug.out;echo;

valgrind: clean s21_matrix_oop.a
	$(CC) tests/test.cc s21_matrix_oop.a $(FLAGS) -o test
# valgrind  --tool=memcheck --track-fds=yes --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test
	valgrind  --tool=memcheck --leak-check=yes ./test

style:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cc *.h
	clang-format -i *.cc *.h
	rm .clang-format

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.h *.cc
	
clean:
	rm -rf *.o *.a test
	rm -rf *.gcno *gcda *.gcov gcov *.html *.css
	rm -rf report report.info
	@echo;echo "Clean complete";echo;
