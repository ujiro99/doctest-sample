CC = g++
LIBS = -pthread
CFLAGS = -g -Wall -MMD -MP -coverage -fprofile-arcs -ftest-coverage
LDFLAGS = -lgcov -coverage

# directories
SRC_DIR = ../src
INC_DIR = ../inc
LIB_DIR = lib

# files
BIN = test_fibonacci
SRCS = $(shell find . -name "*.cpp")
EXCLUDE = $(shell find ./$(LIB_DIR) -type f)
INCS = $(filter-out $(EXCLUDE), $(shell find . -name "*.hpp"))
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

# tasks
all: format $(BIN)
	mv $(BIN) ../

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(SRC_DIR) -I$(LIB_DIR) -o $@ -c $<

format:
	@for src in $(INCS) $(SRCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@echo "Done"

CLEAN_TARGETS = $(BIN) \
				*.o *.d *.cpp-* *.hpp-* *.gcno *.gcda \
				**/*.o **/*.d **/*.cpp-* **/*.hpp-* **/*.gcno **/*.gcda
clean:
	rm -rf $(CLEAN_TARGETS)

-include $(DEPS)

.PHONY: all format clean
