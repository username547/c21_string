CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
LDFLAGS = -L. s21_string.a -lm -lcheck -lsubunit
AR = ar
ARFLAGS = rcs

REPORT_DIR = gcov_report

TEST_EXEC = s21_string_test

SRC_LIB = s21_string.c parser.c handlers.c converters.c
OBJ_LIB = $(SRC_LIB:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: clean s21_string.a

s21_string.a: $(OBJ_LIB)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@

test: clean s21_string.a
	$(CC) $(CFLAGS) --coverage main.c -o $(TEST_EXEC) $(SRC_LIB) $(LDFLAGS)
	./$(TEST_EXEC)

gcov_report: test
	mkdir -p $(REPORT_DIR)
	lcov --capture --directory . --output-file $(REPORT_DIR)/report.info
	genhtml $(REPORT_DIR)/report.info --output-directory $(REPORT_DIR)

rebuild: clean all

clean:
	rm -rf $(REPORT_DIR) $(TEST_EXEC) *.a *.o *.gcda *.gcno
