CC = g++
LIBS =
CFLAGS = -g -Wall
LDFLAGS =

TARGETS = fibonacci
TEST_TARGETS = test_fibonacci

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj
TEST_DIR = ./test

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
TESTS = $(wildcard $(TEST_DIR)/*.cpp)
INCS = $(wildcard $(INC_DIR)/*.hpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
TEST_OBJ = $(addprefix $(TEST_DIR)/, $(notdir $(TESTS:.cpp=.o)))
DEPENDS = $(OBJS:.o=.d)

all: format $(TARGETS) $(TEST_TARGETS) report

$(TARGETS): $(OBJS) $(LIBS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if [ ! -d $(OBJ_DIR) ]; \
		then echo "mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR); \
		fi
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

$(TEST_TARGETS): $(TEST_OBJ) $(LIBS)
	$(CC) -o $@ $(TEST_OBJ) $(OBJS) $(LDFLAGS) -lgcov --coverage

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CFLAGS) -coverage -fprofile-arcs -ftest-coverage -I$(INC_DIR) -o $@ -c $<

format:
	@for src in $(INCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@for src in $(SRCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@echo "Done"

docs:
	@doxygen

clean:
	$(RM) $(TARGETS) $(TEST_TARGETS) $(OBJS) $(DEPENDS)

report:
	./$(TEST_TARGETS) 2>&1 > test_result.txt
	gcovr --xml --output=gcover_result.xml $(SRC_DIR)
	cppcheck --enable=all --xml --suppress=missingIncludeSystem -I $(INC_DIR) $(SRC_DIR) 2> cppcheck_result.xml

-include $(DEPENDS)

.PHONY: all test clean docs report
