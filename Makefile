CC = g++
LIBS =
CFLAGS = -g -Wall -MMD -MP
LDFLAGS =

# output files
TARGETS = fibonacci

# directories
SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

# files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
INCS = $(wildcard $(INC_DIR)/*.hpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPS = $(OBJS:.o=.d)

# tasks
all: format $(TARGETS)

$(TARGETS): $(OBJS) $(LIBS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@if [ ! -d $(OBJ_DIR) ]; \
		then echo "mkdir -p $(OBJ_DIR)"; mkdir -p $(OBJ_DIR); \
		fi
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $@ -c $<

FORMAT_TARGETS = $(INCS) $(SRCS)
format:
	@for src in $(FORMAT_TARGETS) ; do \
		echo "Formatting $$src..." ; \
		clang-format -i "$$src" ; \
	done
	@echo "Done"

docs:
	@doxygen

CLEAN_TARGETS = $(TARGETS) **/*.o **/*.d **/*.cpp-* **/*.hpp-* **/*.gcno **/*.gcda
clean:
	$(RM) $(CLEAN_TARGETS)

.PHONY: all clean docs

-include $(DEPS)
include test.mk
