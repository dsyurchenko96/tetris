CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
LDFLAGS = -lncurses
GCOV_FLAGS = -ftest-coverage -fprofile-arcs -fPIC

BACKEND_DIR = brick_game/tetris
FRONTEND_DIR = gui/cli
TEST_DIR = tests
BUILD_DIR = build
DOXYGEN_DIR = doxygen_output
HEADER_DIR = inc

INSTALLED_FILE = game
ARCHIVE_DIR = archive

SRC = $(wildcard $(BACKEND_DIR)/*.c)
OBJ = $(SRC:$(BACKEND_DIR)/%.c=$(BUILD_DIR)/%.o)
GCOV_OBJ = $(SRC:$(BACKEND_DIR)/%.c=$(BUILD_DIR)/%.gcno)
GCOV_OBJ_O = $(SRC:$(BACKEND_DIR)/%.c=$(BUILD_DIR)/%.gcov.o)

TEST_SRC = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJ = $(patsubst $(TEST_DIR)/test%.c, $(BUILD_DIR)/test%.o, $(TEST_SRC))

TARGET = tetris

# CHECK FOR SYSTEM
UNAME:=$(shell uname -s)
ifeq ($(UNAME), Linux)
 CFLAGS += -D_XOPEN_SOURCE=600 # for random()
 TEST_FLAGS = -pthread -lcheck -lrt -lm -lsubunit
 OPENER = xdg-open
else ifeq ($(UNAME), Darwin)
#  ifeq ($(shell uname -m), arm64)
#   CC = gcc-14
#  endif
 TEST_FLAGS = $(shell pkg-config --cflags --libs check)
 OPENER = open
endif

all: $(TARGET)

$(TARGET): $(TARGET).a
	$(CC) $(CFLAGS) -c main.c -o $(BUILD_DIR)/main.o
	$(CC) $(CFLAGS) -c $(FRONTEND_DIR)/frontend.c -o $(BUILD_DIR)/frontend.o
	$(CC) $(CFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/frontend.o $(TARGET).a -o $(BUILD_DIR)/$(TARGET) $(LDFLAGS)

$(TARGET).a: $(OBJ)
	ar rcs $(TARGET).a $^
	ranlib $(TARGET).a

$(BUILD_DIR)/%.o: $(BACKEND_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR)/%.gcov.o: $(BACKEND_DIR)/%.c
	$(CC) -c $(CFLAGS) $(GCOV_FLAGS) -o $@ $<

$(TEST_OBJ): $(BUILD_DIR)/test_%.o: $(TEST_DIR)/test_%.c
	$(CC) -c $(CFLAGS) -o $@ $< --coverage

play: clean $(TARGET)
	./$(BUILD_DIR)/$(TARGET)
	
covered: $(GCOV_OBJ_O)
	ar rcs $(TARGET).a $(GCOV_OBJ_O)
	ranlib $(TARGET).a

test.a: $(TEST_OBJ)
	ar rcs $(BUILD_DIR)/test.a $^
	ranlib $(BUILD_DIR)/test.a

test_compile: clean covered test.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(TEST_DIR)/test_suite.c -o $(BUILD_DIR)/test_suite.o --coverage
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(BUILD_DIR)/test_suite.o $(BUILD_DIR)/test.a $(TARGET).a -o $(BUILD_DIR)/test $(LDFLAGS) $(TEST_FLAGS)

test: test_compile
	./$(BUILD_DIR)/test

gcov_report: test
	lcov -t "$(TARGET)" -o $(BUILD_DIR)/$(TARGET).info -c -d .
	genhtml -o $(BUILD_DIR)/gcov_report $(BUILD_DIR)/$(TARGET).info
	$(OPENER) ./$(BUILD_DIR)/gcov_report/index.html

style:
	clang-format -i -style=file:"../materials/linters/.clang-format" $(BACKEND_DIR)/*.c $(FRONTEND_DIR)/*.c $(TEST_DIR)/*.c $(TEST_DIR)/*.h *.c $(HEADER_DIR)/*.h

clean:
	rm -rf $(BUILD_DIR)/* $(TARGET).a $(TARGET) $(DOXYGEN_DIR)/ $(INSTALLED_FILE) $(INSTALLED_FILE).tar.gz $(ARCHIVE_DIR)

install: all
	install $(BUILD_DIR)/$(TARGET) $(INSTALLED_FILE)

uninstall:
	rm $(INSTALLED_FILE)

dist: clean
	mkdir -p $(ARCHIVE_DIR)
	tar -cvzf $(ARCHIVE_DIR)/$(INSTALLED_FILE).tar.gz *

untar: dist
	cd $(ARCHIVE_DIR) && tar xvf $(INSTALLED_FILE).tar.gz

dvi:
	doxygen Doxyfile
	$(OPENER) $(DOXYGEN_DIR)/html/index.html
	make -C $(DOXYGEN_DIR)/latex

rebuild:
	make clean
	make all

statictest:
	cppcheck --enable=all --suppress=missingIncludeSystem .

beforecommit:
	make style
	make statictest
	make clean

debug: rebuild
	lldb $(BUILD_DIR)/$(TARGET)

test_leaks: test_compile
ifeq ($(UNAME), Linux)
	valgrind --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(BUILD_DIR)/test
else ifeq ($(UNAME), Darwin)
	leaks --atExit -- ./$(BUILD_DIR)/test
endif

docker:
	cd ../materials/build/Docker && bash run.sh

.PHONY: all clean test test_compile test_leaks gcov_report style debug docker rebuild beforecommit play covered