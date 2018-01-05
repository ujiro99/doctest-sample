TEST_CFLAGS = -g -Wall -MMD -MP -coverage -fprofile-arcs -ftest-coverage
TEST_LDFLAGS = -lgcov -coverage

# output files
TEST_TARGETS = test_fibonacci
TEST_RESULT  = test_result.txt
COV_RESULT   = gcover_result.xml
CEHCK_RESULT = cppcheck_result.xml

# directories
TEST_DIR = test

# add files to Makefiles's task.
FORMAT_TARGETS += $(TEST_SRCS)
CLEAN_TARGETS += $(TEST_TARGETS) $(TEST_RESULT) $(COV_RESULT) $(CEHCK_RESULT)

# files
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(addprefix $(TEST_DIR)/, $(notdir $(TEST_SRCS:.cpp=.o)))
TEST_DEPS = $(TEST_OBJS:.o=.d)

# tasks
test: format $(TEST_TARGETS)
	./$(TEST_TARGETS) 2>&1 | tee $(TEST_RESULT)

$(TEST_TARGETS): $(TEST_OBJS) $(LIBS)
	$(CC) -o $@ $(TEST_OBJS) $(TEST_LDFLAGS)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(TEST_CFLAGS) -I$(INC_DIR) -I$(SRC_DIR) -o $@ -c $<

report:
	gcovr --xml --output=$(COV_RESULT) -e '$(TEST_DIR)/doctest.h' -e '$(TEST_DIR)/test_.*.cpp' -v -r .
	cppcheck --enable=all --xml --suppress=missingIncludeSystem -I $(INC_DIR) $(SRC_DIR) 2> $(CEHCK_RESULT)

-include $(TEST_DEPS)

.PHONY: test clean report
