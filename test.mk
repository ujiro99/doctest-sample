CC = g++
LIBS =
CFLAGS = -g -Wall -coverage -fprofile-arcs -ftest-coverage
LDFLAGS = -lgcov -coverage

# output files
TEST_TARGETS = test_fibonacci
TEST_RESULT  = test_result.txt
COV_RESULT   = gcover_result.xml
CEHCK_RESULT = cppcheck_result.xml

# directories
SRC_DIR  = ./src
INC_DIR  = ./inc
TEST_DIR = ./test

# files
SRCS = $(wildcard $(TEST_DIR)/*.cpp)
OBJS = $(addprefix $(TEST_DIR)/, $(notdir $(SRCS:.cpp=.o)))

# tasks
test: format $(TEST_TARGETS) report

$(TEST_TARGETS): $(OBJS) $(LIBS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(SRC_DIR) -o $@ -c $<

format:
	@for src in $(SRCS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@echo "Done"

clean:
	$(RM) \
		$(TEST_TARGETS) \
		$(TEST_RESULT) \
		$(COV_RESULT) \
		$(CEHCK_RESULT)

report:
	./$(TEST_TARGETS) 2>&1 > $(TEST_RESULT)
	gcovr --xml --output=$(COV_RESULT) -e test/doctest.h -e test/test_*.cpp -r .
	cppcheck --enable=all --xml --suppress=missingIncludeSystem -I $(INC_DIR) $(SRC_DIR) 2> $(CEHCK_RESULT)

.PHONY: test clean report
