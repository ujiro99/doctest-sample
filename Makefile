CC = g++
LIBS = -pthread
CFLAGS = -g -Wall -MMD -MP
LDFLAGS =

# output files
TARGETS = fibonacci
COVERAGE = gcover_result.xml
CPPCHECK = cppcheck_result.xml
TEST_TARGETS = test_fibonacci
TEST_RESULT = test_result.txt

# directories
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
TEST_DIR = test
LIB_DIR = $(TEST_DIR)/lib

# files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
INCS = $(wildcard $(INC_DIR)/*.hpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS = $(OBJS:.o=.d)

# tasks
all: format $(TARGETS)

$(TARGETS): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if [ ! -d $(OBJ_DIR) ]; \
		then echo "mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR); \
		fi
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

format:
	@for src in $(INCS) $(SRCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@echo "Done"

docs:
	@doxygen

report: $(TEST_DIR)
	./$(TEST_TARGETS) 2>&1 | tee $(TEST_RESULT)
	gcovr --xml --output=$(COVERAGE) -e '$(LIB_DIR)/.*' -e '$(TEST_DIR)/test.*.cpp' -e '$(TEST_DIR)/mock.*.cpp' -v -r .
	cppcheck --enable=all --xml --suppress=missingIncludeSystem -I $(INC_DIR) $(SRC_DIR) 2> $(CPPCHECK)

$(TEST_DIR):
	$(MAKE) -C $@

CLEAN_TARGETS = $(TARGETS) $(COVERAGE) $(CPPCHECK) $(TEST_TARGETS) $(TEST_RESULT) $(OBJ_DIR) \
				**/*.o **/*.d **/*.cpp-* **/*.hpp-* **/*.gcno **/*.gcda
clean:
	rm -rf $(CLEAN_TARGETS)

.PHONY: all format docs report $(TEST_DIR) clean

-include $(DEPS)
